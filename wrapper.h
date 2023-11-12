#ifndef WRAPPER_H
#define WRAPPER_H

//#include "core/object/ref_counted.h"

#include "core/object/class_db.h"
#include "core/templates/rid.h"


/*
class SocialEngineResponse : public RID_Data
{
public:
    RID self;

    String response;
};
*/

class SocialEngineServer : public Object
{
public:

	GDCLASS(SocialEngineServer, Object);

protected:
    static void _bind_methods();
    /*
    {
        ClassDB::bind_method(D_METHOD("generate_npc_response", "dialogue", "appearance", "personality", "knowledge"), &SocialEngine::generate_npc_response);
    }
    */
public:
    static SocialEngineServer* get_singleton() {
        static SocialEngineServer instance;  // Guaranteed to be destroyed; Instantiated on first use
        return &instance;
    }
    String generate_npc_response(String dialog);
	void load_LLMs();
	~SocialEngineServer();

private:
    SocialEngineServer();
};





#endif // WRAPPER_H
