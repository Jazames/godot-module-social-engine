#include "register_types.h"
#include "core/object/class_db.h"
#include "wrapper.h"
//#include "social_engine.h"


//*
void initialize_social_engine_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}

    ClassDB::register_class<SocialEngineServer>();
    //ObjectTypeDB::register_type<Appearance>();
    //ObjectTypeDB::register_type<Knowledge>();
    //ObjectTypeDB::register_type<Personality>();
}

void uninitialize_social_engine_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
    //nothing to do here
}
//*/
