#ifndef SERVERPLUGIN_PYTHON_H
#define SERVERPLUGIN_PYTHON_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#define SERVERPLUGIN_ENGINEPYTHON_VERSION "1.0"
#define SERVERPLUGIN_ENGINEPYTHON_CLASS CServerEnginePython
//#define SERVERPLUGIN_ENGINEPYTHON_VAR g_ServerEnginePython

class SERVERPLUGIN_ENGINEPYTHON_CLASS
{
public:
	SERVERPLUGIN_ENGINEPYTHON_CLASS();
	~SERVERPLUGIN_ENGINEPYTHON_CLASS();

	// Called when python try to load
	// ok = true if all loads correctly, otherwise false
	virtual void OnPythonLoad(bool ok) = 0;
};

extern bool isPythonEnabled;

#ifdef PYTHON
//=================================================================================
// Includes
//=================================================================================
#include "Python.h"


//=================================================================================
// Python related globals
//=================================================================================
extern PyMethodDef VAR_PYTHON_METHODS[]; // Holds all of our python methods.

//=================================================================================
// Python command class ( Courtesy of Mattie Casper )
//=================================================================================
class PyCommand
{
public:
	PyCommand(char *name, PyCFunction pFunc, unsigned int method, char *desc)
	{
		static int i = 0;
		VAR_PYTHON_METHODS[i].ml_name = name;
		VAR_PYTHON_METHODS[i].ml_meth = pFunc;
		VAR_PYTHON_METHODS[i].ml_flags = method;
		VAR_PYTHON_METHODS[i].ml_doc = desc;
		i++;
		VAR_PYTHON_METHODS[i].ml_name = 0;
		VAR_PYTHON_METHODS[i].ml_meth = 0;
		VAR_PYTHON_METHODS[i].ml_flags = 0;
		VAR_PYTHON_METHODS[i].ml_doc = 0;
	}
};

//=================================================================================
// Useful Macros
//=================================================================================
#define DECLARE_PYCMD( name, docstring ) \
	static PyObject * PYTHON_FUNCTION_PREFIX##name(PyObject *self, PyObject *args); \
	static PyCommand PYTHON_FUNCTION_PREFIX##name##_cmd( #name, PYTHON_FUNCTION_PREFIX##name, METH_VARARGS, docstring ); \
	static PyObject * PYTHON_FUNCTION_PREFIX##name(PyObject *self, PyObject *args)

//=================================================================================
// Functions
//=================================================================================
bool EnablePython();
#endif

#endif