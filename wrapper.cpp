
#include "wrapper.h"
#include "social.h"


String SocialEngine::generate_npc_response(String dialogue)
{
    std::string words = std::string(dialogue.ascii().get_data());
    std::string reply = get_default_response(words);
    String response = String(reply.c_str());
    return response;
}


//*
void SocialEngine::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("generate_npc_response", "dialogue"), &SocialEngine::generate_npc_response);
} 
//*/

SocialEngine::SocialEngine()
{
	//nothing to do here
}
