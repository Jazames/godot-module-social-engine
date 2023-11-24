#ifndef WRAPPER_H
#define WRAPPER_H

//#include "core/object/ref_counted.h"

#include "core/object/class_db.h"
#include "core/templates/rid.h"
#include "core/object/ref_counted.h"
#include "social-engine/SocialEngine/social.h"



class SocialEngineResponse : public RefCounted
{
	GDCLASS(SocialEngineResponse, RefCounted);
public:
    RID self;

    String get_response();
	bool is_complete();

	SocialEngineResponse();
	void set_response_ptr(std::shared_ptr<DialogueResponse> ptr);

	SocialEngineResponse(const SocialEngineResponse &other);
	SocialEngineResponse(SocialEngineResponse &&other) noexcept;
	SocialEngineResponse &operator=(SocialEngineResponse &&other) noexcept;

protected:
	static void _bind_methods();

private:
	std::shared_ptr<DialogueResponse> response_ptr;
};







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
	Ref<SocialEngineResponse> generate_npc_response(String dialog);
	void load_LLMs();
	~SocialEngineServer();

private:
    SocialEngineServer();
};





#endif // WRAPPER_H
