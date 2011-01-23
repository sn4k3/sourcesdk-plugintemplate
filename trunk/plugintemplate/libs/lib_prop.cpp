//=================================================================================
// Includes
//=================================================================================
#include "includes/lotsofstuff.h"

//=================================================================================
// Constructor / Destructor
//=================================================================================
LIB_PROP_CLASS::LIB_PROP_CLASS(){}
LIB_PROP_CLASS::~LIB_PROP_CLASS()
{
	vec_props.RemoveAll();
	vec_gameprops.RemoveAll();
}

//=================================================================================
// Load 
//=================================================================================
bool LIB_PROP_CLASS::Load(KeyValues *kvProps)
{
	if(!kvProps) return false;
	if(kvProps->IsEmpty())
	{
		//kvProps->deleteThis();
		return true;
	}
	KeyValues *kvLoop;
	for(kvLoop = kvProps->GetFirstValue(); kvLoop; kvLoop = kvLoop->GetNextValue())
	{
		const char *name = kvLoop->GetName();
		if(!name) continue;
		const char *value = kvLoop->GetString();
		if(!value)
		{
			DevMsg("[WARNING] Props: %s got no value, skip this\n", name);
			continue;
		}
		AddOrReplaceCombinedPropToConfig(name, value);
		//kvLoop->deleteThis();
	}
	//kvProps->deleteThis();
	return true;
}

// Add a combined prop to config list, but never write to file
bool LIB_PROP_CLASS::AddCombinedPropToConfig(const char *name, const char *combinedprop)
{
	if(GetCombinedPropIndexFromConfig(name) != -1)
		return false;
	vec_gameprops.AddToTail(std::make_pair(name, combinedprop));
	DevMsg("Prop: Adding %s to list, with %s as combinedprop\n", name, combinedprop);
	return true;
}

// Add or Replace a combined prop from config list, but never write to file
bool LIB_PROP_CLASS::AddOrReplaceCombinedPropToConfig(const char *name, const char *combinedprop)
{
	if(!AddCombinedPropToConfig(name, combinedprop))
		return ReplaceCombinedPropFromConfig(name, combinedprop);
	return true;
}

// Replace a combined prop from config list, but never write to file
bool LIB_PROP_CLASS::ReplaceCombinedPropFromConfig(const char *name, const char *combinedprop)
{
	int index = GetCombinedPropIndexFromConfig(name);
	if(index == -1)
		return false;
	vec_gameprops[index].second = combinedprop;
	return true;
}

// Remove a combined prop from config list, but never write to file
bool LIB_PROP_CLASS::RemoveCombinedPropToConfig(const char *name, const char *combinedprop)
{
	int index = GetCombinedPropIndexFromConfig(name);
	if(index == -1)
		return false;
	vec_gameprops.Remove(index);
	return true;
}

// Get the index from list of a combined prop stored on the game configs ie. common.txt and cstrike.txt
int LIB_PROP_CLASS::GetCombinedPropIndexFromConfig(const char *name)
{
	FOR_EACH_VEC(vec_gameprops, i)
		if(LIB_STRING_CLASS::FStrEq(vec_gameprops[i].first, name))
			return i;
	return -1;
}

// Get a combined prop stored on the game configs ie. common.txt and cstrike.txt
const char *LIB_PROP_CLASS::GetCombinedPropFromConfig(const char *name, const char *defaultValue /*= NULL*/)
{
	FOR_EACH_VEC(vec_gameprops, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_gameprops[i].first, name))
			return vec_gameprops[i].second;
	}
	return defaultValue;
}

void LIB_PROP_CLASS::DumpProps(const char *ClassName /*= NULL*/)
{

	ServerClass *sc = VAR_IFACE_GAMESERVERDLL->GetAllServerClasses();

	Msg(""PLUGIN_HEADER"Dumping props:\n");
	while(sc)
	{
		int NumProps = sc->m_pTable->GetNumProps();
		const char *thatClassname = sc->GetName();
		if(ClassName)
		{
			if(strcmp(thatClassname, ClassName) == 0)
			{
				for (int i = 0; i < NumProps; i++)
				{
					Msg("[%i] %s.%s\n",i, ClassName, (sc->m_pTable->GetProp(i)->GetName()));
				}
			}
		}
		else
		{
			for (int i = 0; i < NumProps; i++)
			{
				Msg("[%i] %s.%s\n",i, thatClassname, (sc->m_pTable->GetProp(i)->GetName()));
			}
		}
		sc = sc->m_pNext;
	}
}

// Split 'CBasePlayer.m_iHealth' into ClassName = CBasePlayer, Property = m_iHealth
bool LIB_PROP_CLASS::SplitCombinedProp(const char *source, char *ClassName, char *Property)
{
	int length = strlen(source);

	bool found_split = false;
	int j = 0;

	for (int i = 0; i < length; i++)
	{
		if (found_split)
		{
			Property[j] = source[i];
			j++;
		}
		else
		{
			ClassName[i] = source[i];
		}

		if (!found_split)
		{
			if (source[i] == '.')
			{
				ClassName[i] = '\0';
				found_split = true;
			}
		}
	}

	if (!found_split) return false;

	return true;
}

// Calcutate prop field type
LIB_PROP_CLASS::PropType LIB_PROP_CLASS::CalculatePropType(Property_t *cprop)
{
	return CalculatePropType(cprop->var_type, cprop->bits, cprop->is_signed);
}

// Calcutate prop field type
LIB_PROP_CLASS::PropType LIB_PROP_CLASS::CalculatePropType(int var_type, int bits, bool is_signed)
{
	switch (var_type)
	{
	case DPT_Int:
		if (bits == 1)
		{
			return PROP_BOOL;
		}
		else if (bits <= 8)
		{
			if (is_signed)
			{
				return PROP_CHAR;
			}
			else
			{
				return PROP_UNSIGNED_CHAR;
			}
		}
		else if (bits <= 16)
		{
			if (is_signed)
			{
				return PROP_SHORT;
			}
			else
			{
				return PROP_UNSIGNED_SHORT;
			}
		}
		else
		{
			if (is_signed)
			{
				return PROP_INT;
			}
 
			return PROP_UNSIGNED_INT;
		}
	case DPT_Float: return PROP_FLOAT;
	case DPT_String:
		if (is_signed)
		{
			return PROP_CHAR_PTR;
		}
		else
		{
			return PROP_UNSIGNED_CHAR_PTR;
		}
	case DPT_Vector: return PROP_VECTOR;
	case DPT_VectorXY: return PROP_VECTOR2D;
	default: break;
	}

	return PROP_INVALID;
}

/**
* Searches for a named Server Class.
*
* @param name		Name of the top-level server class.
* @return 		Server class matching the name, or NULL if none found.
*/
ServerClass *LIB_PROP_CLASS::UTIL_FindServerClass(const char *name)
{
	ServerClass *pClass = VAR_IFACE_GAMESERVERDLL->GetAllServerClasses();
	while (pClass)
	{
		if (strcmp(pClass->m_pNetworkName, name) == 0)
			return pClass;
		pClass = pClass->m_pNext;
	}
	return NULL;
}

/*
* Recursively looks through a send table for a given named property.
*
* @param pTable	Send table to browse.
* @param name		Property to search for.
* @return 		SendProp pointer on success, NULL on failure.
*/
SendProp *LIB_PROP_CLASS::UTIL_FindSendProp(SendTable *pTable, const char *name)
{
	int count = pTable->GetNumProps();
	SendProp *pProp;
	for (int i = 0; i < count; i++)
	{
		pProp = pTable->GetProp(i);
		if (strcmp(pProp->GetName(), name) == 0)
			return pProp;
		if (pProp->GetDataTable())
		{
			if ((pProp=UTIL_FindSendProp(pProp->GetDataTable(), name)) != NULL)
				return pProp;
		}
	}
	return NULL;
}

int LIB_PROP_CLASS::FindPropOffset(const char *combinedprop)
{
	char ClassName[256] = "";
	char Property[256] = "";
	if(!SplitCombinedProp(combinedprop, ClassName, Property)) return 0;
	return FindPropOffset(ClassName, Property);
}

int LIB_PROP_CLASS::FindPropOffset(const char *ClassName, const char *Property)
{
	Property_t *cprop = FindProperty(ClassName, Property);
	if(!cprop->propertyname) return -1;
	return cprop->offset;
}

LIB_PROP_CLASS::Property_t *LIB_PROP_CLASS::FindProperty(const char *combinedprop)
{
	char ClassName[256] = "";
	char Property[256] = "";
	if(!SplitCombinedProp(combinedprop, ClassName, Property)) return NULL;
	return FindProperty(ClassName, Property);
}

LIB_PROP_CLASS::Property_t *LIB_PROP_CLASS::FindProperty(const char *ClassName, const char *Property)
{
	if(!ClassName) return NULL; // No data
	if(!Property) return FindProperty(ClassName); // Maybe a combined prop?

	FOR_EACH_VEC(vec_props, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_props[i]->classname, ClassName) && LIB_STRING_CLASS::FStrEq(vec_props[i]->propertyname, Property))
		{
			return vec_props[i];
		}
	}
	ServerClass *sc = UTIL_FindServerClass(ClassName);
	if(!sc)	return NULL;

//	CUtlVector<const char *>* propSplit = LIB_STRING_CLASS::StrSplit(Property, '.');

	/*SendProp *pProp = NULL;
	SendTable *pTable = sc->m_pTable;
	int zero = 0;
	int& offset = zero;
	//int offset = 0;
	for(int i = 0; i < propSplit->Count(); i++)
	{		
		pProp = UTIL_FindSendProp(pTable, propSplit->Element(i), offset);
		if(!pProp)	return CProperty();
		Msg("Element: %s - %i\n", propSplit->Element(i), pProp->GetOffset());
		offset += pProp->GetOffset();
		pTable = pProp->GetDataTable();
	}*/

	SendProp *pProp = UTIL_FindSendProp(sc->m_pTable, Property);
	if(!pProp)	return NULL;

	Property_t *cprop = new Property_t();
	cprop->classname = LIB_STRING_CLASS::StrNew(ClassName);
	cprop->propertyname = LIB_STRING_CLASS::StrNew(Property);
	cprop->offset = pProp->GetOffset();
	cprop->bits = pProp->m_nBits;
	cprop->is_signed = pProp->IsSigned();
	cprop->var_type = pProp->GetType();
	cprop->type = CalculatePropType(cprop);
	vec_props.AddToTail(cprop);
	return cprop;

/*	ServerClass *sc = server->GetAllServerClasses();
	CUtlVector<const char *>* propSplit = LIB_STRING_CLASS::StrSplit(Property, '.');
	while(sc)
	{
		if(strcmp(sc->GetName(), ClassName) == 0)
		{
			int NumProps = sc->m_pTable->GetNumProps();
			for (int i = 0; i < NumProps; i++)
			{
				SendProp *prop = sc->m_pTable->GetProp(i);
				int index = 0;
				i = 0;
				while(prop)
				{
					Msg("Element: %s\n",propSplit->Element(i));
					if (strcmp(prop->GetName(), propSplit->Element(i)) == 0)
					{
						index += prop->GetOffset();
						i++;
						if(!(propSplit->Count()-1) == i)
						{
							prop = prop->GetDataTable()->;
							continue;
						}
						propSplit->~CUtlVector();
						CProperty cprop;
						cprop.classname = ClassName;
						cprop.propertyname = Property;
						cprop.offset = index;
						cprop.bits = prop->m_nBits;
						cprop.is_signed = prop->IsSigned();
						cprop.var_type = prop->GetType();
						vec_props.AddToTail(cprop);
						return cprop;
					}
				}
			}
			return CProperty();
		}
		sc = sc->m_pNext;
	}
	
	return CProperty();*/
}
const char *LIB_PROP_CLASS::Prop_GetDynamic(edict_t *pEntity, const char *ClassName, const char *Property)
{
	Property_t *cprop = FindProperty(ClassName, Property);
	if(!cprop) return false;
	if(cprop->type == PROP_BOOL)
	{
		bool value = Prop_GetBool(pEntity, ClassName, Property);
		return LIB_STRING_CLASS::StrFormat("%i", value);
	}
	if(cprop->type == PROP_UNSIGNED_SHORT)
	{
		unsigned short value = Prop_GetUnsignedShort(pEntity, ClassName, Property);
		return LIB_STRING_CLASS::StrFormat("%hd", value);
	}
	if(cprop->type == PROP_SHORT)
	{
		short value = Prop_GetShort(pEntity, ClassName, Property);
		return LIB_STRING_CLASS::StrFormat("%hd", value);
	}
	if(cprop->type == PROP_UNSIGNED_INT)
	{
		unsigned int value = Prop_GetUnsignedInt(pEntity, ClassName, Property);
		return LIB_STRING_CLASS::StrFormat("%u", value);
	}
	if(cprop->type == PROP_INT)
	{
		int value = Prop_GetInt(pEntity, ClassName, Property);
		return LIB_STRING_CLASS::StrFormat("%i", value);
	}
	if(cprop->type == PROP_FLOAT)
	{
		float value = Prop_GetFloat(pEntity, ClassName, Property);
		return LIB_STRING_CLASS::StrFormat("%f", value);
	}
	if(cprop->type == PROP_UNSIGNED_CHAR)
	{
		unsigned char value = Prop_GetUnsignedChar(pEntity, ClassName, Property);
		return LIB_STRING_CLASS::StrFormat("%c", value);
	}
	if(cprop->type == PROP_CHAR)
	{
		char value = Prop_GetChar(pEntity, ClassName, Property);
		return LIB_STRING_CLASS::StrFormat("%c", value);
	}
	if(cprop->type == PROP_UNSIGNED_CHAR_PTR)
	{
		unsigned char *value = Prop_GetUnsignedCharPtr(pEntity, ClassName, Property);
		return reinterpret_cast<const char *>(value);
	}
	if(cprop->type == PROP_CHAR_PTR)
	{
		char *value = Prop_GetCharPtr(pEntity, ClassName, Property);
		return value;
	}
	if(cprop->type == PROP_QANGLE)
	{
		QAngle *value = Prop_GetQAngle(pEntity, ClassName, Property);
		if(!value->IsValid()) return NULL;
		return LIB_STRING_CLASS::StrFormat("%f %f %f", value->x, value->y, value->z);
	}
	if(cprop->type == PROP_VECTOR)
	{
		Vector *value = Prop_GetVector(pEntity, ClassName, Property);
		if(!value->IsValid()) return NULL;
		return LIB_STRING_CLASS::StrFormat("%f %f %f", value->x, value->y, value->z);
	}
	if(cprop->type == PROP_VECTOR2D)
	{
		Vector2D *value = Prop_GetVector2D(pEntity, ClassName, Property);
		if(!value->IsValid()) return NULL;
		return LIB_STRING_CLASS::StrFormat("%f %f", value->x, value->y);
	}
	return false;
}

int	LIB_PROP_CLASS::Prop_GetVal(edict_t *pEntity, const char *ClassName, const char *Property, int default_value)
{
	Property_t *cprop = FindProperty(ClassName, Property);
	if(!cprop) return false;
	switch(cprop->type)
	{
	case PROP_BOOL:return Prop_GetBool(pEntity, ClassName, Property);
	case PROP_UNSIGNED_SHORT:return Prop_GetUnsignedShort(pEntity, ClassName, Property);
	case PROP_SHORT:return Prop_GetShort(pEntity, ClassName, Property);
	case PROP_UNSIGNED_INT:return Prop_GetUnsignedInt(pEntity, ClassName, Property);
	case PROP_INT:return Prop_GetInt(pEntity, ClassName, Property);
	case PROP_CHAR:return Prop_GetChar(pEntity, ClassName, Property);
	case PROP_UNSIGNED_CHAR:return Prop_GetChar(pEntity, ClassName, Property);
	default : break;
	}
	return default_value;
}

char *LIB_PROP_CLASS::Prop_GetVal(edict_t *pEntity, const char *ClassName, const char *Property, char *default_value)
{
	Property_t *cprop = FindProperty(ClassName, Property);
	if(!cprop) return false;
	switch(cprop->type)
	{
	case PROP_CHAR_PTR:return Prop_GetCharPtr(pEntity, ClassName, Property);
	case PROP_UNSIGNED_CHAR_PTR:return (char *) Prop_GetUnsignedCharPtr(pEntity, ClassName, Property);
	default : break;
	}
	return default_value;
}

void *LIB_PROP_CLASS::Prop_GetVoidPtr(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return 0;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	void *iptr = (void *)ptr;
	return iptr;
}

unsigned int LIB_PROP_CLASS::Prop_GetUnsignedInt(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return 0;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	unsigned int *iptr = (unsigned int *)ptr;
	return *iptr;
}

int LIB_PROP_CLASS::Prop_GetInt(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return -1;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	int *iptr = (int *)ptr;
	return *iptr;
}

unsigned long LIB_PROP_CLASS::Prop_GetUnsignedLong(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return 0;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	unsigned long *iptr = (unsigned long *)ptr;
	return *iptr;
}

long LIB_PROP_CLASS::Prop_GetLong(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return -1;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	long *iptr = (long *)ptr;
	return *iptr;
}

unsigned char LIB_PROP_CLASS::Prop_GetUnsignedChar(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	return *ptr;
}

char LIB_PROP_CLASS::Prop_GetChar(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	char *cptr = (char *)ptr;
	return *cptr;
}

unsigned short LIB_PROP_CLASS::Prop_GetUnsignedShort(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return 0;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	unsigned short *sptr = (unsigned short *) ptr;
	return *sptr;
}

short LIB_PROP_CLASS::Prop_GetShort(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return -1;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	short *sptr = (short *) ptr;
	return *sptr;
}

float LIB_PROP_CLASS::Prop_GetFloat(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return -1;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	float *sptr = (float *) ptr;
	return *sptr;
}

unsigned char *LIB_PROP_CLASS::Prop_GetUnsignedCharPtr(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	unsigned char  *cptr = (unsigned char *) ptr;
	return cptr;
}

char *LIB_PROP_CLASS::Prop_GetCharPtr(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	char  *cptr = (char *) ptr;
	return cptr;
}

bool LIB_PROP_CLASS::Prop_GetBool(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	bool *iptr = (bool *) ptr;
	return *iptr;
}

QAngle *LIB_PROP_CLASS::Prop_GetQAngle(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	QAngle *iptr = (QAngle *) ptr;
	return iptr;
}

Vector *LIB_PROP_CLASS::Prop_GetVector(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	Vector *iptr = (Vector *) ptr;
	return iptr;
}

Vector2D *LIB_PROP_CLASS::Prop_GetVector2D(edict_t *pEntity, const char *ClassName, const char *Property)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	Vector2D *iptr = (Vector2D *) ptr;
	return iptr;
}

/*****************************
*			Prop SET
*****************************/

bool LIB_PROP_CLASS::Prop_SetDynamic(edict_t *pEntity, const char *ClassName, const char *Property, const char *value)
{
	Property_t *cprop = FindProperty(ClassName, Property);
	if(!cprop) return false;
	switch(cprop->type)
	{
	case PROP_BOOL:
		return Prop_SetBool(pEntity, ClassName, Property, (!LIB_STRING_CLASS::StrIsNULL(value) || LIB_STRING_CLASS::FStrEq(value, "true")));
	case PROP_UNSIGNED_SHORT:
		return Prop_SetUnsignedShort(pEntity, ClassName, Property, static_cast<unsigned short>(atoi(value)));
	case PROP_SHORT:
		return Prop_SetShort(pEntity, ClassName, Property, static_cast<short>(atoi(value)));
	case PROP_UNSIGNED_INT:
		return Prop_SetUnsignedInt(pEntity, ClassName, Property, static_cast<unsigned int>(atoi(value)));
	case PROP_INT:
		return Prop_SetInt(pEntity, ClassName, Property, atoi(value));
	case PROP_FLOAT:
		return Prop_SetFloat(pEntity, ClassName, Property, atof(value));
		break;
	case PROP_UNSIGNED_CHAR:
		return Prop_SetUnsignedChar(pEntity, ClassName, Property, (unsigned char)*value);
	case PROP_CHAR:
		return Prop_SetChar(pEntity, ClassName, Property, (char)*value);
	case PROP_UNSIGNED_CHAR_PTR:
		return Prop_SetUnsignedCharPtr(pEntity, ClassName, Property, (unsigned char *)value);
	case PROP_CHAR_PTR:
		return Prop_SetCharPtr(pEntity, ClassName, Property, (char*)value);
	//case PROP_QANGLE:
	//	return Prop_SetQAngle(pEntity, ClassName, Property, LIB_STRING_CLASS::StrToAngle(value));
	//case PROP_VECTOR:
	//	return Prop_SetVector(pEntity, ClassName, Property, LIB_STRING_CLASS::StrToVec(value));
	//case PROP_COLOUR:
	}
	if(cprop->type = PROP_QANGLE)
	{
		QAngle angle = LIB_STRING_CLASS::StrToAngle(value);
		return Prop_SetQAngle(pEntity, ClassName, Property, angle);
	}
	if(cprop->type = PROP_VECTOR)
	{
		Vector vector = LIB_STRING_CLASS::StrToVec(value);
		return Prop_SetVector(pEntity, ClassName, Property, vector);
	}
	return false;
}

bool LIB_PROP_CLASS::Prop_SetVal(edict_t *pEntity, const char *ClassName, const char *Property, int value)
{
	Property_t *cprop = FindProperty(ClassName, Property);
	if(!cprop) return false;
	switch(cprop->type)
	{
	case PROP_BOOL:Prop_SetBool(pEntity, ClassName, Property, static_cast<bool>((((value == 0) ? false:true))));break;
	case PROP_UNSIGNED_SHORT:Prop_SetUnsignedShort(pEntity, ClassName, Property, static_cast<unsigned short>(value));break;
	case PROP_SHORT:Prop_SetShort(pEntity, ClassName, Property, static_cast<short>(value));break;
	case PROP_UNSIGNED_INT:Prop_SetUnsignedInt(pEntity, ClassName, Property, value);break;
	case PROP_INT:Prop_SetInt(pEntity, ClassName, Property, value);break;
	case PROP_UNSIGNED_CHAR:Prop_SetChar(pEntity, ClassName, Property, value);break;
	case PROP_CHAR:Prop_SetChar(pEntity, ClassName, Property, static_cast<char>(value));break;
	default : return false;
	}
	return true;
}

bool LIB_PROP_CLASS::Prop_SetVal(edict_t *pEntity, const char *ClassName, const char *Property, char *value)
{
	Property_t *cprop = FindProperty(ClassName, Property);
	if(!cprop) return false;
	switch(cprop->type)
	{
	case PROP_CHAR_PTR:Prop_SetCharPtr(pEntity, ClassName, Property, value);break;
	case PROP_UNSIGNED_CHAR_PTR:Prop_SetUnsignedCharPtr(pEntity, ClassName, Property, (unsigned char *) value);break;
	default : return false;
	}

	return true;
}


bool LIB_PROP_CLASS::Prop_SetUnsignedInt(edict_t *pEntity, const char *ClassName, const char *Property, unsigned int value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	unsigned int *iptr = (unsigned int *) ptr;
	*iptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetInt(edict_t *pEntity, const char *ClassName, const char *Property, int value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	int *iptr = (int *) ptr;
	*iptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetUnsignedLong(edict_t *pEntity, const char *ClassName, const char *Property, unsigned long value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	unsigned long *iptr = (unsigned long *) ptr;
	*iptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetLong(edict_t *pEntity, const char *ClassName, const char *Property, long value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	long *iptr = (long *) ptr;
	*iptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetUnsignedChar(edict_t *pEntity, const char *ClassName, const char *Property, unsigned char value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) (pEntity->GetUnknown() + offset);
	*ptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetChar(edict_t *pEntity, const char *ClassName, const char *Property, char value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	char *cptr = (char *) ptr;
	*cptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetUnsignedShort(edict_t *pEntity, const char *ClassName, const char *Property, unsigned short value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	unsigned short *sptr = (unsigned short *) ptr;
	*sptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetShort(edict_t *pEntity, const char *ClassName, const char *Property, short value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	short *sptr = (short *) ptr;
	*sptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetFloat(edict_t *pEntity, const char *ClassName, const char *Property, float value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	float *sptr = (float *) ptr;
	*sptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetUnsignedCharPtr(edict_t *pEntity, const char *ClassName, const char *Property, unsigned char *value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	unsigned char *sptr = (unsigned char *) ptr;
	sptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetCharPtr(edict_t *pEntity, const char *ClassName, const char *Property, char *value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	char *sptr = (char *) ptr;
	sptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetBool(edict_t *pEntity, const char *ClassName, const char *Property, bool value)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	bool *sptr = (bool *) ptr;
	*sptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetQAngle(edict_t *pEntity, const char *ClassName, const char *Property, QAngle &value)
{
	if(!value.IsValid()) return false;
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	QAngle *sptr = (QAngle *) ptr;
	*sptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetVector(edict_t *pEntity, const char *ClassName, const char *Property, Vector &value)
{
	if(!value.IsValid()) return false;
	if(!value.IsZero()) return false;
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	Vector *sptr = (Vector *) ptr;
	*sptr = value;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

bool LIB_PROP_CLASS::Prop_SetColor(edict_t *pEntity, const char *ClassName, const char *Property, byte r, byte g, byte b, byte a)
{
	int offset = FindPropOffset(ClassName, Property);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
	color32 *cptr = (color32 *) ptr;
	cptr->r = r;
	cptr->g = g;
	cptr->b = b;
	cptr->a = a;
    pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;
}

//=================================================================================
// Datamap Functions
//=================================================================================

// Search datamap for value
int	LIB_PROP_CLASS::FindDatamapOffset(CBaseEntity *pCBE, const char *name)
{
#ifndef USE_LIB_VFUNCS
	return -1;
#else
	Datamap_t *dmap_t = FindDatamap(pCBE, name);
	return dmap_t ? dmap_t->offset : -1;
#endif
}

// Search datamap for value
LIB_PROP_CLASS::Datamap_t *LIB_PROP_CLASS::FindDatamap(CBaseEntity *pCBE, const char *name)
{
#ifndef USE_LIB_VFUNCS
	return NULL;
#else
	if(!name) return NULL;
	if(!pCBE) return NULL;
	FOR_EACH_VEC(vec_datamap, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_datamap[i]->name, name))
			return vec_datamap[i];
	}
	datamap_t *dmap = VAR_LIB_VFUNCS->CBaseEntity_GetDataDescMap(pCBE);
	if (!dmap) return NULL;
	PropType type = PROP_INVALID;
	while (dmap)
	{
		for ( int i = 0; i < dmap->dataNumFields; i++ )
		{
			if (dmap->dataDesc[i].fieldName && strcmp(name,dmap->dataDesc[i].fieldName) == 0)
			{
				switch(dmap->dataDesc[i].fieldType)
				{
					case FIELD_FLOAT: type = PROP_FLOAT; break;
					//case FIELD_STRING: type = PROP_CHAR_PTR; break;
					case FIELD_STRING: type = PROP_STRING; break;
					case FIELD_INTEGER: type = PROP_INT; break;
					case FIELD_BOOLEAN: type = PROP_BOOL; break;
					case FIELD_SHORT: type = PROP_SHORT; break;
					case FIELD_CHARACTER: type = PROP_CHAR; break;
					case FIELD_VECTOR: type = PROP_VECTOR; break;
					case FIELD_VECTOR2D: type = PROP_VECTOR2D; break;
					case FIELD_COLOR32: type = PROP_COLOUR; break;
					case FIELD_EHANDLE: type = PROP_EHANDLE; break;
					case FIELD_EDICT: type = PROP_EDICT; break;
					default: type = PROP_INVALID;
				}
				Datamap_t *dmap_t = new Datamap_t();
				dmap_t->name = LIB_STRING_CLASS::StrNew(name);
				dmap_t->offset = dmap->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL];
				dmap_t->type = type;
				vec_datamap.AddToTail(dmap_t);
				return dmap_t;
			}
		}

		dmap = dmap->baseMap;
	}
	return NULL;
#endif
}

const char *LIB_PROP_CLASS::Map_GetDynamic(CBaseEntity *pCBE, const char *name)
{
	Datamap_t *datamap_t = FindDatamap(pCBE, name);
	if(!datamap_t) return false;
	if(datamap_t->type == PROP_BOOL)
	{
		bool value = Map_GetBool(pCBE, name);
		return LIB_STRING_CLASS::StrFormat("%i", value);
	}
	if(datamap_t->type == PROP_SHORT)
	{
		short value = Map_GetShort(pCBE, name);
		return LIB_STRING_CLASS::StrFormat("%hd", value);
	}
	if(datamap_t->type == PROP_INT)
	{
		int value = Map_GetInt(pCBE, name);
		return LIB_STRING_CLASS::StrFormat("%i", value);
	}
	if(datamap_t->type == PROP_FLOAT)
	{
		float value = Map_GetFloat(pCBE, name);
		return LIB_STRING_CLASS::StrFormat("%f", value);
	}
	if(datamap_t->type == PROP_CHAR)
	{
		char value = Map_GetChar(pCBE, name);
		return LIB_STRING_CLASS::StrFormat("%c", value);
	}
	if(datamap_t->type == PROP_CHAR_PTR)
	{
		char *value = Map_GetCharPtr(pCBE, name);
		return value;
	}
	if(datamap_t->type == PROP_STRING)
	{
		string_t value = Map_GetString(pCBE, name);
		return value.ToCStr();
	}
	if(datamap_t->type == PROP_VECTOR)
	{
		Vector *value = Map_GetVector(pCBE, name);
		if(!value->IsValid()) return NULL;
		return LIB_STRING_CLASS::StrFormat("%f %f %f", value->x, value->y, value->z);
	}
	if(datamap_t->type == PROP_VECTOR2D)
	{
		Vector2D *value = Map_GetVector2D(pCBE, name);
		if(!value->IsValid()) return NULL;
		return LIB_STRING_CLASS::StrFormat("%f %f", value->x, value->y);
	}
	if(datamap_t->type == PROP_COLOUR)
	{
		color32 value = *Map_GetColor(pCBE, name);
		return LIB_STRING_CLASS::StrFormat("%c %c %c", value.r, value.g, value.b, value.a);
	}
	if(datamap_t->type == PROP_EHANDLE)
	{
		CBaseHandle *value = Map_GetEHandle(pCBE, name);
		return LIB_STRING_CLASS::StrFormat("%i", value->ToInt());
	}
	return false;
}

bool LIB_PROP_CLASS::Map_SetDynamic(CBaseEntity *pCBE, const char *name, const char *value)
{
	Datamap_t *datamap_t = FindDatamap(pCBE, name);
	if(!datamap_t) return false;
	DevMsg("Datamap set dynamic: %s [%i]\n", name, datamap_t->offset);
	switch(datamap_t->type)
	{
	case PROP_BOOL:
		return Map_SetBool(pCBE, name, (!LIB_STRING_CLASS::StrIsNULL(value) || LIB_STRING_CLASS::FStrEq(value, "true")));
	case PROP_SHORT:
		return Map_SetShort(pCBE, name, static_cast<short>(atoi(value)));
	case PROP_INT:
		return Map_SetInt(pCBE, name, atoi(value));
	case PROP_FLOAT:

		return Map_SetFloat(pCBE, name, atof(value));
	case PROP_CHAR:
		return Map_SetChar(pCBE, name, atoi(value));
	case PROP_CHAR_PTR:
		return Map_SetCharPtr(pCBE, name, (char*)value);
	case PROP_STRING:
		return Map_SetString(pCBE, name, value);
	//case PROP_VECTOR:
	//	return Map_SetVector(pCBE, name, LIB_STRING_CLASS::StrToVec(value));
	//case PROP_COLOUR:
	//	return Map_SetColor(pCBE, name, LIB_STRING_CLASS::StrToColor32(value));
	}
	if(datamap_t->type = PROP_VECTOR)
	{
		Vector vector = LIB_STRING_CLASS::StrToVec(value);
		return Map_SetVector(pCBE, name, vector);
	}
	if(datamap_t->type = PROP_COLOUR)
	{
		color32 color = LIB_STRING_CLASS::StrToColor32(value);
		return Map_SetColor(pCBE, name, color);
	}
	return false;
}

int	LIB_PROP_CLASS::Map_GetVal(CBaseEntity *pCBE, const char *name, int default_value)
{
	Datamap_t *datamap_t = FindDatamap(pCBE, name);
	if(!datamap_t) return default_value;
	switch(datamap_t->type)
	{
	case PROP_BOOL:return Map_GetBool(pCBE, name);
	case PROP_INT:return Map_GetInt(pCBE, name);
	case PROP_CHAR:return Map_GetChar(pCBE, name);
	case PROP_SHORT:return Map_GetShort(pCBE, name);
	default : break;
	}

	return default_value;
}

bool LIB_PROP_CLASS::Map_SetVal(CBaseEntity *pCBE, const char *name, int value)
{
	Datamap_t *datamap_t = FindDatamap(pCBE, name);
	if(!datamap_t) return false;
	switch(datamap_t->type)
	{
	case PROP_BOOL:Map_SetBool(pCBE, name, static_cast<bool>((((value == 0) ? false:true))));break;
	case PROP_INT:Map_SetInt(pCBE, name, value);break;
	case PROP_CHAR:Map_SetChar(pCBE, name, static_cast<char>(value));break;
	case PROP_SHORT:Map_SetShort(pCBE, name, static_cast<short>(value));break;
	default : return false;
	}

	return true;
}

void *LIB_PROP_CLASS::Map_GetVoidPtr(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	void *iptr = (void *)ptr;
	return iptr;
}

int LIB_PROP_CLASS::Map_GetInt(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return -1;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	int *iptr = (int *)ptr;
	return *iptr;
}

bool LIB_PROP_CLASS::Map_SetInt(CBaseEntity *pCBE, const char *name, int value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	int *iptr = (int *) ptr;
	*iptr = value;
	return true;
}

float LIB_PROP_CLASS::Map_GetFloat(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return -1;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	float *fptr = (float *)ptr;
	return *fptr;
}

bool LIB_PROP_CLASS::Map_SetFloat(CBaseEntity *pCBE, const char *name, float value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	float *fptr = (float *) ptr;
	*fptr = value;
	return true;
}

char LIB_PROP_CLASS::Map_GetChar(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	char *cptr = (char *)ptr;
	return *cptr;
}

bool LIB_PROP_CLASS::Map_SetChar(CBaseEntity *pCBE, const char *name, char value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	char *iptr = (char *) ptr;
	*iptr = value;
	return true;
}

short LIB_PROP_CLASS::Map_GetShort(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return -1;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	short *sptr = (short *) ptr;
	return *sptr;
}

bool LIB_PROP_CLASS::Map_SetShort(CBaseEntity *pCBE, const char *name, short value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	short *sptr = (short *) ptr;
	*sptr = value;
	return true;
}

char *LIB_PROP_CLASS::Map_GetCharPtr(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	char  *cptr = (char *) ptr;
	return cptr;
}

bool LIB_PROP_CLASS::Map_SetCharPtr(CBaseEntity *pCBE, const char *name, char *value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	char *cptr = (char *) ptr;
	cptr = value;
	return true;
}

string_t LIB_PROP_CLASS::Map_GetString(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return MAKE_STRING("");
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	string_t  *sptr = (string_t *) ptr;
	return *sptr;
}

bool LIB_PROP_CLASS::Map_SetString(CBaseEntity *pCBE, const char *name, const char *value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	string_t *sptr = (string_t *) ptr;
	*sptr = MAKE_STRING(value);
	return true;
}

bool LIB_PROP_CLASS::Map_GetBool(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	bool *bptr = (bool *) ptr;
	return *bptr;
}

bool LIB_PROP_CLASS::Map_SetBool(CBaseEntity *pCBE, const char *name, bool value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	bool *bptr = (bool *) ptr;
	*bptr = value;
	return true;
}

Vector *LIB_PROP_CLASS::Map_GetVector(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	Vector *bptr = (Vector *) ptr;
	return bptr;
}

bool LIB_PROP_CLASS::Map_SetVector(CBaseEntity *pCBE, const char *name, Vector &value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	Vector *bptr = (Vector *) ptr;
	*bptr = value;
	return true;
}

Vector2D *LIB_PROP_CLASS::Map_GetVector2D(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	Vector2D *bptr = (Vector2D *) ptr;
	return bptr;
}

bool LIB_PROP_CLASS::Map_SetVector2D(CBaseEntity *pCBE, const char *name, Vector2D &value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	Vector2D *bptr = (Vector2D *) ptr;
	*bptr = value;
	return true;
}

color32 *LIB_PROP_CLASS::Map_GetColor(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	color32 *cptr = (color32 *) ptr;
	return cptr;
}

bool LIB_PROP_CLASS::Map_SetColor(CBaseEntity *pCBE, const char *name, byte r, byte g, byte b, byte a)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	color32 *cptr = (color32 *) ptr;
	cptr->r = r;
	cptr->g = g;
	cptr->b = b;
	cptr->a = a;
	return true;
}

bool LIB_PROP_CLASS::Map_SetColor(CBaseEntity *pCBE, const char *name, color32 &value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	color32 *cptr = (color32 *) ptr;
	*cptr = value;
	return true;
}

CBaseEntity *LIB_PROP_CLASS::Map_GetCBaseEntity(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	CBaseEntity *cptr = (CBaseEntity *) ptr;
	return cptr;
}

bool LIB_PROP_CLASS::Map_SetCBaseEntity(CBaseEntity *pCBE, const char *name, CBaseEntity *value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	CBaseEntity *cptr = (CBaseEntity *) ptr;
	cptr = value;
	return true;
}

edict_t *LIB_PROP_CLASS::Map_GetEdict(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	edict_t *cptr = (edict_t *) ptr;
	return cptr;
}

bool LIB_PROP_CLASS::Map_SetEdict(CBaseEntity *pCBE, const char *name, edict_t *value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	edict_t *cptr = (edict_t *) ptr;
	cptr = value;
	return true;
}

CBaseHandle *LIB_PROP_CLASS::Map_GetEHandle(CBaseEntity *pCBE, const char *name)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return NULL;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	CBaseHandle *cptr = (CBaseHandle *) ptr;
	return cptr;
}

bool LIB_PROP_CLASS::Map_SetEHandle(CBaseEntity *pCBE, const char *name, CBaseHandle *value)
{
	int offset = FindDatamapOffset(pCBE, name);
	if(offset == -1) return false;
	unsigned char *ptr = (unsigned char *) pCBE + offset;
	CBaseHandle *cptr = (CBaseHandle *) ptr;
	cptr = value;
	return true;
}

bool LIB_PROP_CLASS::Map_CanUseMap()
{
#ifdef USE_LIB_VFUNCS 
	return false;
#else
	return true;
#endif
}
