
#include "wrapper.h"
#include "social-engine/SocialEngine/social.h"
#include <iostream>
#include "core/object/object.h"




String SocialEngineResponse::get_response() {
	if (response_ptr)
	{
		std::string r = response_ptr->get_response();
		return String(r.c_str());
	}
	return String("Thinking");
}

bool SocialEngineResponse::is_complete()
{
	if (response_ptr) {
		return response_ptr->get_is_complete();
	}
	else {
		return false;
	}
}

SocialEngineResponse::SocialEngineResponse()
{
}

void SocialEngineResponse::set_response_ptr(std::shared_ptr<DialogueResponse> ptr) {
	response_ptr = ptr;
}

void SocialEngineResponse::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_response"), &SocialEngineResponse::get_response);
	ClassDB::bind_method(D_METHOD("is_complete"), &SocialEngineResponse::is_complete);
}


SocialEngineResponse::SocialEngineResponse(const SocialEngineResponse &other) {
	// Deep copy or shared copy of other.response_ptr
	response_ptr = other.response_ptr;
}
//*/

SocialEngineResponse::SocialEngineResponse(SocialEngineResponse &&other) noexcept
		:
		response_ptr(std::move(other.response_ptr)) {
	// Other move operations
}

SocialEngineResponse &SocialEngineResponse::operator=(SocialEngineResponse &&other) noexcept {
	if (this != &other) {
		response_ptr = std::move(other.response_ptr);
		// Other move operations
	}
	return *this;
}

Ref<SocialEngineResponse> SocialEngineServer::generate_npc_response(String dialogue) {
    std::string words = std::string(dialogue.ascii().get_data());

	std::shared_ptr<DialogueResponse> r_ptr = get_default_response(words);
	//SocialEngineResponse response;
	//response.set_response_ptr(r_ptr);

	Ref<SocialEngineResponse> ref_response;
	ref_response.instantiate();
	ref_response->set_response_ptr(r_ptr);
	return ref_response;

	/*
    std::string reply = get_default_response(words);
    String response = String(reply.c_str());
    return response;
	*/
}

void SocialEngineServer::load_LLMs()
{
	init_social_engine();
}


//*
void SocialEngineServer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("generate_npc_response", "dialogue"), &SocialEngineServer::generate_npc_response);
	ClassDB::bind_method(D_METHOD("load_LLMs"), &SocialEngineServer::load_LLMs);
} 
//*/

SocialEngineServer::SocialEngineServer()
{
	std::cout << "SocialEngine::SocialEngine() called\n" << std::endl;
	//init_social_engine();
	//std::string what = get_default_response("Where can I find a tincture to heal my headache?");
	//std::cout << what << std::endl;
}

SocialEngineServer::~SocialEngineServer()
{
	std::cout << "SocialEngine::~SocialEngine() called" << std::endl;
	deinit_social_engine();
}
