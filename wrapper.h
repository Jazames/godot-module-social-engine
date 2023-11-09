#ifndef WRAPPER_H
#define WRAPPER_H

//#include "core/object/ref_counted.h"

#include "core/object/class_db.h"


class SocialEngine : public Object
{
public:

	GDCLASS(SocialEngine, Object);

protected:
    static void _bind_methods();
    /*
    {
        ClassDB::bind_method(D_METHOD("generate_npc_response", "dialogue", "appearance", "personality", "knowledge"), &SocialEngine::generate_npc_response);
    }
    */
public:
    String generate_npc_response(String dialog);

    SocialEngine();
};





#endif // WRAPPER_H
