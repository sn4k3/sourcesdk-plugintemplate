//=================================================================================
// Includes
//=================================================================================
#include "includes/default.h"
#include PLUGIN_MAIN_INCLUDE

PLUGIN_PYTHON_CLASS::PLUGIN_PYTHON_CLASS()
{}

PLUGIN_PYTHON_CLASS::~PLUGIN_PYTHON_CLASS()
{}

// Override
// Called when python try to load
// ok = true if all loads correctly, otherwise false
void PLUGIN_PYTHON_CLASS::OnPythonLoad(bool ok)
{
	// Variable: isPythonEnabled is a global with ok content
	if(ok)
	{
		Msg(""PLUGIN_MSG_PREFIX" Python is running\n");
		return;
	}
}

#ifdef PYTHON // Use your python functions under this define
DECLARE_PYCMD(Msg, "Print text to console")
{
	char		*szText;

	if( !PyArg_ParseTuple(args, "s", &szText) )
	{
		Msg("Could not parse function arguments.\n");
		return Py_BuildValue("i", 0);
	}

	Msg(szText);

	return Py_BuildValue("i", 1);
}
#endif

//=================================================================================
// Global variable, never touch
//=================================================================================
PLUGIN_PYTHON_CLASS *VAR_PLUGIN_PYTHON;