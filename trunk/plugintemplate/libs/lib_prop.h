#ifndef LIB_PROP_H
#define LIB_PROP_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#define LIB_PROP_VERSION "1.0"
#define LIB_PROP_CLASS CPropLib

/*#define SET_PROP(_pEntity, _className, _property, _type, _value) \
	int offset = FindPropOffset(_className, _property);
	if(!offset) return false;
	unsigned char *ptr = (unsigned char *) _pEntity->GetUnknown() + offset;
	_type cptr = (_type) ptr;
	*cptr = _value;
    _pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
	return true;*/

class SendProp;

class LIB_PROP_CLASS
{
public:
	enum PropType
	{
		PROP_INVALID = 0,
		PROP_INT,
		PROP_UNSIGNED_CHAR,
		PROP_CHAR_PTR,
		PROP_CHAR,
		PROP_SHORT,
		PROP_UNSIGNED_SHORT,
		PROP_BOOL,
		PROP_UNSIGNED_INT,
		PROP_FLOAT,
		PROP_UNSIGNED_CHAR_PTR,
		PROP_QANGLE,
		PROP_VECTOR,
		PROP_VECTOR2D,
		PROP_COLOUR,

		// Datamap only
		PROP_STRING,
		PROP_CLASSPTR, // CBaseEntity*
		PROP_EHANDLE,  // Entity handle
		PROP_EDICT     // edict_t *

	};

	struct Property_t
	{
		// ClassName
		const char *classname;
		// Property Name
		const char *propertyname;
		// Offset
		int offset;

		int bits;

		// Is Signed? unsigned = false
		bool is_signed;

		// Variable type
		int var_type;

		PropType type;

		Property_t(){ classname = propertyname = NULL;  offset = bits = var_type = -1; type = PROP_INVALID; is_signed = false; }
	};

	struct Datamap_t
	{
		const char *name;

		int offset;

		PropType type;

		Datamap_t(){ name = NULL; offset = -1; type = PROP_INVALID;}
	};

	

	LIB_PROP_CLASS();
	~LIB_PROP_CLASS();

	bool Load(KeyValues *kvProps);
	

	// Add a combined prop to config list, but never write to file
	bool AddCombinedPropToConfig(const char *name, const char *combinedprop);

	// Add or Replace a combined prop from config list, but never write to file
	bool AddOrReplaceCombinedPropToConfig(const char *name, const char *combinedprop);

	// Replace a combined prop from config list, but never write to file
	bool ReplaceCombinedPropFromConfig(const char *name, const char *combinedprop);

	// Remove a combined prop from config list, but never write to file
	bool RemoveCombinedPropToConfig(const char *name, const char *combinedprop);

	// Get the index from list of a combined prop stored on the game configs ie. common.txt and cstrike.txt
	int GetCombinedPropIndexFromConfig(const char *name);

	// Get a combined prop stored on the game configs ie. common.txt and cstrike.txt
	const char *GetCombinedPropFromConfig(const char *name, const char *defaultValue /*= NULL*/);

	static void DumpProps(const char *ClassName = NULL);

	// Split 'CBasePlayer.m_iHealth' into ClassName = CBasePlayer, Property = m_iHealth
	static bool SplitCombinedProp(const char *source, char *ClassName, char *Property);

	static PropType CalculatePropType(Property_t *cprop);
	static PropType CalculatePropType(int var_type, int bits, bool is_signed);

	ServerClass *UTIL_FindServerClass(const char *name);
	SendProp *UTIL_FindSendProp(SendTable *pTable, const char *name);
	int FindPropOffset(const char *combinedprop);
	int FindPropOffset(const char *ClassName, const char *Property);
	Property_t *FindProperty(const char *combinedprop);
	Property_t *FindProperty(const char *ClassName, const char *Property);

	template<typename T> T Prop_Get(edict_t *pEntity, const char *ClassName, const char *Property)
	{
		int offset = FindPropOffset(ClassName, Property);
		if(!offset == -1) return NULL;
		unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
		T *iptr = (T *)ptr;
		return *iptr;
	}
	const char		*Prop_GetDynamic(edict_t *pEntity, const char *ClassName, const char *Property);
	int				Prop_GetVal(edict_t *pEntity, const char *ClassName, const char *Property, int default_value);
	char			*Prop_GetVal(edict_t *pEntity, const char *ClassName, const char *Property, char *default_value);
	void			*Prop_GetVoidPtr(edict_t *pEntity, const char *ClassName, const char *Property);
	unsigned int	Prop_GetUnsignedInt(edict_t *pEntity, const char *ClassName, const char *Property);
	int				Prop_GetInt(edict_t *pEntity, const char *ClassName, const char *Property);
	unsigned long	Prop_GetUnsignedLong(edict_t *pEntity, const char *ClassName, const char *Property);
	long			Prop_GetLong(edict_t *pEntity, const char *ClassName, const char *Property);
	unsigned char	Prop_GetUnsignedChar(edict_t *pEntity, const char *ClassName, const char *Property);
	char			Prop_GetChar(edict_t *pEntity, const char *ClassName, const char *Property);
	unsigned short	Prop_GetUnsignedShort(edict_t *pEntity, const char *ClassName, const char *Property);
	short			Prop_GetShort(edict_t *pEntity, const char *ClassName, const char *Property);
	float			Prop_GetFloat(edict_t *pEntity, const char *ClassName, const char *Property);
	unsigned char	*Prop_GetUnsignedCharPtr(edict_t *pEntity, const char *ClassName, const char *Property);
	char			*Prop_GetCharPtr(edict_t *pEntity, const char *ClassName, const char *Property);
	bool			Prop_GetBool(edict_t *pEntity, const char *ClassName, const char *Property);
	QAngle			*Prop_GetQAngle(edict_t *pEntity, const char *ClassName, const char *Property);
	Vector			*Prop_GetVector(edict_t *pEntity, const char *ClassName, const char *Property);
	Vector2D		*Prop_GetVector2D(edict_t *pEntity, const char *ClassName, const char *Property);

	//Sets

	template<typename T> bool Prop_Set(edict_t *pEntity, const char *ClassName, const char *Property, T value)
	{
		int offset = FindPropOffset(ClassName, Property);
		if(!offset == -1) return false;
		unsigned char *ptr = (unsigned char *) pEntity->GetUnknown() + offset;
		T *iptr = (T *) ptr;
		*iptr = value;
		pEntity->m_fStateFlags |= FL_EDICT_CHANGED;
		return true;
	}
	bool Prop_SetDynamic(edict_t *pEntity, const char *ClassName, const char *Property, const char *value);
	bool Prop_SetVal(edict_t *pEntity, const char *ClassName, const char *Property, int value);
	bool Prop_SetVal(edict_t *pEntity, const char *ClassName, const char *Property, char *value);
	bool Prop_SetUnsignedInt(edict_t *pEntity, const char *ClassName, const char *Property, unsigned int value);
	bool Prop_SetInt(edict_t *pEntity, const char *ClassName, const char *Property, int value);
	bool Prop_SetUnsignedLong(edict_t *pEntity, const char *ClassName, const char *Property, unsigned long value);
	bool Prop_SetLong(edict_t *pEntity, const char *ClassName, const char *Property, long value);
	bool Prop_SetUnsignedChar(edict_t *pEntity, const char *ClassName, const char *Property, unsigned char value);
	bool Prop_SetChar(edict_t *pEntity, const char *ClassName, const char *Property, char value);
	bool Prop_SetUnsignedShort(edict_t *pEntity, const char *ClassName, const char *Property, unsigned short value);
	bool Prop_SetShort(edict_t *pEntity, const char *ClassName, const char *Property, short value);
	bool Prop_SetFloat(edict_t *pEntity, const char *ClassName, const char *Property, float value);
	bool Prop_SetUnsignedCharPtr(edict_t *pEntity, const char *ClassName, const char *Property, unsigned char *value);
	bool Prop_SetCharPtr(edict_t *pEntity, const char *ClassName, const char *Property, char *value);
	bool Prop_SetBool(edict_t *pEntity, const char *ClassName, const char *Property, bool value);
	bool Prop_SetQAngle(edict_t *pEntity, const char *ClassName, const char *Property, QAngle &value);
	bool Prop_SetVector(edict_t *pEntity, const char *ClassName, const char *Property, Vector &value);
	bool Prop_SetColor(edict_t *pEntity, const char *ClassName, const char *Property, byte r, byte g, byte b, byte a);


	// Search datamap for value
	int	FindDatamapOffset(CBaseEntity *pCBE, const char *name);


	// Search datamap for value
	Datamap_t *FindDatamap(CBaseEntity *pCBE, const char *name);

	template<typename T> T Map_Get(CBaseEntity *pCBE, const char *name)
	{
		int offset = FindDatamapOffset(pCBE, name);
		if(!offset == -1) return NULL;
		unsigned char *ptr = (unsigned char *) pCBE + offset;
		T *iptr = (T *)ptr;
		return *iptr;
	}
	const char *Map_GetDynamic(CBaseEntity *pCBE, const char *name);
	void		*Map_GetVoidPtr(CBaseEntity *pCBE, const char *name);
	int			Map_GetVal(CBaseEntity *pCBE, const char *name, int default_value);
	int			Map_GetInt(CBaseEntity *pCBE, const char *name);
	float		Map_GetFloat(CBaseEntity *pCBE, const char *name);
	char		Map_GetChar(CBaseEntity *pCBE, const char *name);
	short		Map_GetShort(CBaseEntity *pCBE, const char *name);
	char		*Map_GetCharPtr(CBaseEntity *pCBE, const char *name);
	string_t	Map_GetString(CBaseEntity *pCBE, const char *name);
	bool		Map_GetBool(CBaseEntity *pCBE, const char *name);
	Vector		*Map_GetVector(CBaseEntity *pCBE, const char *name);
	Vector2D	*Map_GetVector2D(CBaseEntity *pCBE, const char *name);
	color32		*Map_GetColor(CBaseEntity *pCBE, const char *name);
	CBaseEntity *Map_GetCBaseEntity(CBaseEntity *pCBE, const char *name);
	edict_t		*Map_GetEdict(CBaseEntity *pCBE, const char *name);
	CBaseHandle *Map_GetEHandle(CBaseEntity *pCBE, const char *name);

	template<typename T> bool Map_Set(CBaseEntity *pCBE, const char *name, T value)
	{
		int offset = FindDatamapOffset(pCBE, name);
		if(!offset == -1) return false;
		unsigned char *ptr = (unsigned char *) pCBE + offset;
		T *iptr = (T *) ptr;
		*iptr = value;
		return true;
	}
	bool Map_SetDynamic(CBaseEntity *pCBE, const char *name, const char *value);
	bool Map_SetVal(CBaseEntity *pCBE, const char *name, int value);
	bool Map_SetInt(CBaseEntity *pCBE, const char *name, int value);
	bool Map_SetFloat(CBaseEntity *pCBE, const char *name, float value);
	bool Map_SetChar(CBaseEntity *pCBE, const char *name, char value);
	bool Map_SetShort(CBaseEntity *pCBE, const char *name, short value);
	bool Map_SetCharPtr(CBaseEntity *pCBE, const char *name, char *value);
	bool Map_SetString(CBaseEntity *pCBE, const char *name, const char *value);
	bool Map_SetBool(CBaseEntity *pCBE, const char *name, bool value);
	bool Map_SetVector(CBaseEntity *pCBE, const char *name, Vector &value);
	bool Map_SetVector2D(CBaseEntity *pCBE, const char *name, Vector2D &value);
	bool Map_SetColor(CBaseEntity *pCBE, const char *name, byte r, byte g, byte b, byte a);
	bool Map_SetColor(CBaseEntity *pCBE, const char *name, color32 &value);
	bool Map_SetCBaseEntity(CBaseEntity *pCBE, const char *name, CBaseEntity *value);
	bool Map_SetEdict(CBaseEntity *pCBE, const char *name, edict_t *value);
	bool Map_SetEHandle(CBaseEntity *pCBE, const char *name, CBaseHandle *value);

	// Returns true if you can use Datamap (VFunc lib ON), otherwise false
	bool Map_CanUseMap();
	
private:
	CUtlVector<Property_t *> vec_props;
	CUtlVector<Datamap_t *> vec_datamap;
	CUtlVector<std::pair<const char*, const char*> > vec_gameprops;
};

#endif
