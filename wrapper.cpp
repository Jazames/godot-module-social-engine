
#include "wrapper.h"
#include "social.h"
#include <iostream>
#include "core/object/object.h"


//SocialEngineServer* SocialEngineServer::singleton = NULL;

String SocialEngineServer::generate_npc_response(String dialogue)
{
    std::string words = std::string(dialogue.ascii().get_data());
    std::string reply = get_default_response(words);
    String response = String(reply.c_str());
    return response;
}


//*
void SocialEngineServer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("generate_npc_response", "dialogue"), &SocialEngineServer::generate_npc_response);
} 
//*/

SocialEngineServer::SocialEngineServer()
{
	std::cout << "SocialEngine::SocialEngine() called\n" << std::endl;
	//init_social_engine();
	//std::string what = get_default_response("Hello.");
	//std::cout << what << std::endl;
}

SocialEngineServer::~SocialEngineServer()
{
	std::cout << "SocialEngine::~SocialEngine() called" << std::endl;
	deinit_social_engine();
}
