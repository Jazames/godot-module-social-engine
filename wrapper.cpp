
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

String SocialEngineResponse::get_classification()
{
	if (response_ptr) {
		DialogueType classification = response_ptr->get_classification();
		return String(get_dialogue_type_name(classification).c_str());
	}
	else {
		return String("Thinking");
	}
}

String SocialEngineResponse::get_response_type()
{
	if (response_ptr) {
		DialogueResponseDirection response_direction = response_ptr->get_response_direction();
		return String(get_response_direction_name(response_direction).c_str());
	}
	else {
		return String("Thinking");
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

Ref<SocialEngineResponse> SocialEngineServer::generate_npc_response(String dialogue, Ref<SocialEnginePersonality> personality) {
    std::string words = std::string(dialogue.ascii().get_data());

	Appearance appearance = Appearance();//TODO: have this passed in
	Knowledge knowledge = Knowledge();//TODO: have this passed in

	InteractionParameters parameters;
	parameters.dialogue = words;
	parameters.personality = personality.ptr()->get_underlying_personality();
	parameters.appearance = appearance;
	parameters.knowledge = knowledge;

	std::shared_ptr<DialogueResponse> r_ptr = get_npc_response(parameters);
	//std::shared_ptr<DialogueResponse> r_ptr = get_default_response(words);
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
	ClassDB::bind_method(D_METHOD("generate_npc_response", "dialogue", "personality"), &SocialEngineServer::generate_npc_response);
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

// Big5Traits
void SocialEnginePersonality::set_enthusiasm(double value) { personality.traits.Enthusiasm = value; }
double SocialEnginePersonality::get_enthusiasm() const { return personality.traits.Enthusiasm; }
void SocialEnginePersonality::set_assertiveness(double value) { personality.traits.Assertiveness = value; }
double SocialEnginePersonality::get_assertiveness() const { return personality.traits.Assertiveness; }
void SocialEnginePersonality::set_withdrawal(double value) { personality.traits.Withdrawal = value; }
double SocialEnginePersonality::get_withdrawal() const { return personality.traits.Withdrawal; }
void SocialEnginePersonality::set_volatility(double value) { personality.traits.Volatility = value; }
double SocialEnginePersonality::get_volatility() const { return personality.traits.Volatility; }
void SocialEnginePersonality::set_compassion(double value) { personality.traits.Compassion = value; }
double SocialEnginePersonality::get_compassion() const { return personality.traits.Compassion; }
void SocialEnginePersonality::set_politeness(double value) { personality.traits.Politeness = value; }
double SocialEnginePersonality::get_politeness() const { return personality.traits.Politeness; }
void SocialEnginePersonality::set_industriousness(double value) { personality.traits.Industriousness = value; }
double SocialEnginePersonality::get_industriousness() const { return personality.traits.Industriousness; }
void SocialEnginePersonality::set_orderliness(double value) { personality.traits.Orderliness = value; }
double SocialEnginePersonality::get_orderliness() const { return personality.traits.Orderliness; }
void SocialEnginePersonality::set_openness(double value) { personality.traits.Openness = value; }
double SocialEnginePersonality::get_openness() const { return personality.traits.Openness; }
void SocialEnginePersonality::set_intellect(double value) { personality.traits.Intellect = value; }
double SocialEnginePersonality::get_intellect() const { return personality.traits.Intellect; }


// MoralFoundations
void SocialEnginePersonality::set_care_harm(double value) { personality.morals.care_harm = value; }
double SocialEnginePersonality::get_care_harm() const { return personality.morals.care_harm; }
void SocialEnginePersonality::set_fairness_cheating(double value) { personality.morals.fairness_cheating = value; }
double SocialEnginePersonality::get_fairness_cheating() const { return personality.morals.fairness_cheating; }
void SocialEnginePersonality::set_loyalty_betrayal(double value) { personality.morals.loyalty_betrayal = value; }
double SocialEnginePersonality::get_loyalty_betrayal() const { return personality.morals.loyalty_betrayal; }
void SocialEnginePersonality::set_authority_subversion(double value) { personality.morals.authority_subversion = value; }
double SocialEnginePersonality::get_authority_subversion() const { return personality.morals.authority_subversion; }
void SocialEnginePersonality::set_sanctity_degradation(double value) { personality.morals.sanctity_degradation = value; }
double SocialEnginePersonality::get_sanctity_degradation() const { return personality.morals.sanctity_degradation; }
void SocialEnginePersonality::set_liberty_oppression(double value) { personality.morals.liberty_oppression = value; }
double SocialEnginePersonality::get_liberty_oppression() const { return personality.morals.liberty_oppression; }

// Personality
void SocialEnginePersonality::set_intelligence(double value) { personality.intelligence = value; }
double SocialEnginePersonality::get_intelligence() const { return personality.intelligence; }
void SocialEnginePersonality::set_maturity(double value) { personality.maturity = value; }
double SocialEnginePersonality::get_maturity() const { return personality.maturity; }
void SocialEnginePersonality::set_age(int value) { personality.age = value; }
int SocialEnginePersonality::get_age() const { return personality.age; }
void SocialEnginePersonality::set_personality_override(String value) { personality.personality_override = value.utf8().get_data(); }
String SocialEnginePersonality::get_personality_override() const { return String(personality.personality_override.c_str()); }
void SocialEnginePersonality::set_personality_modifier(String value) { personality.personality_modifier = value.utf8().get_data(); }
String SocialEnginePersonality::get_personality_modifier() const { return String(personality.personality_modifier.c_str()); }

Personality SocialEnginePersonality::get_underlying_personality() const { return personality; }

void SocialEnginePersonality::_bind_methods() {
	// Big5Traits
	ClassDB::bind_method(D_METHOD("set_enthusiasm", "value"), &SocialEnginePersonality::set_enthusiasm);
	ClassDB::bind_method(D_METHOD("get_enthusiasm"), &SocialEnginePersonality::get_enthusiasm);
	ClassDB::bind_method(D_METHOD("set_assertiveness", "value"), &SocialEnginePersonality::set_assertiveness);
	ClassDB::bind_method(D_METHOD("get_assertiveness"), &SocialEnginePersonality::get_assertiveness);
	ClassDB::bind_method(D_METHOD("set_withdrawal", "value"), &SocialEnginePersonality::set_withdrawal);
	ClassDB::bind_method(D_METHOD("get_withdrawal"), &SocialEnginePersonality::get_withdrawal);
	ClassDB::bind_method(D_METHOD("set_volatility", "value"), &SocialEnginePersonality::set_volatility);
	ClassDB::bind_method(D_METHOD("get_volatility"), &SocialEnginePersonality::get_volatility);
	ClassDB::bind_method(D_METHOD("set_compassion", "value"), &SocialEnginePersonality::set_compassion);
	ClassDB::bind_method(D_METHOD("get_compassion"), &SocialEnginePersonality::get_compassion);
	ClassDB::bind_method(D_METHOD("set_politeness", "value"), &SocialEnginePersonality::set_politeness);
	ClassDB::bind_method(D_METHOD("get_politeness"), &SocialEnginePersonality::get_politeness);
	ClassDB::bind_method(D_METHOD("set_industriousness", "value"), &SocialEnginePersonality::set_industriousness);
	ClassDB::bind_method(D_METHOD("get_industriousness"), &SocialEnginePersonality::get_industriousness);
	ClassDB::bind_method(D_METHOD("set_orderliness", "value"), &SocialEnginePersonality::set_orderliness);
	ClassDB::bind_method(D_METHOD("get_orderliness"), &SocialEnginePersonality::get_orderliness);
	ClassDB::bind_method(D_METHOD("set_openness", "value"), &SocialEnginePersonality::set_openness);
	ClassDB::bind_method(D_METHOD("get_openness"), &SocialEnginePersonality::get_openness);
	ClassDB::bind_method(D_METHOD("set_intellect", "value"), &SocialEnginePersonality::set_intellect);
	ClassDB::bind_method(D_METHOD("get_intellect"), &SocialEnginePersonality::get_intellect);

	// MoralFoundations
	ClassDB::bind_method(D_METHOD("set_care_harm", "value"), &SocialEnginePersonality::set_care_harm);
	ClassDB::bind_method(D_METHOD("get_care_harm"), &SocialEnginePersonality::get_care_harm);
	ClassDB::bind_method(D_METHOD("set_fairness_cheating", "value"), &SocialEnginePersonality::set_fairness_cheating);
	ClassDB::bind_method(D_METHOD("get_fairness_cheating"), &SocialEnginePersonality::get_fairness_cheating);
	ClassDB::bind_method(D_METHOD("set_loyalty_betrayal", "value"), &SocialEnginePersonality::set_loyalty_betrayal);
	ClassDB::bind_method(D_METHOD("get_loyalty_betrayal"), &SocialEnginePersonality::get_loyalty_betrayal);
	ClassDB::bind_method(D_METHOD("set_authority_subversion", "value"), &SocialEnginePersonality::set_authority_subversion);
	ClassDB::bind_method(D_METHOD("get_authority_subversion"), &SocialEnginePersonality::get_authority_subversion);
	ClassDB::bind_method(D_METHOD("set_sanctity_degradation", "value"), &SocialEnginePersonality::set_sanctity_degradation);
	ClassDB::bind_method(D_METHOD("get_sanctity_degradation"), &SocialEnginePersonality::get_sanctity_degradation);
	ClassDB::bind_method(D_METHOD("set_liberty_oppression", "value"), &SocialEnginePersonality::set_liberty_oppression);
	ClassDB::bind_method(D_METHOD("get_liberty_oppression"), &SocialEnginePersonality::get_liberty_oppression);

	// Personality
	ClassDB::bind_method(D_METHOD("set_intelligence", "value"), &SocialEnginePersonality::set_intelligence);
	ClassDB::bind_method(D_METHOD("get_intelligence"), &SocialEnginePersonality::get_intelligence);
	ClassDB::bind_method(D_METHOD("set_maturity", "value"), &SocialEnginePersonality::set_maturity);
	ClassDB::bind_method(D_METHOD("get_maturity"), &SocialEnginePersonality::get_maturity);
	ClassDB::bind_method(D_METHOD("set_age", "value"), &SocialEnginePersonality::set_age);
	ClassDB::bind_method(D_METHOD("get_age"), &SocialEnginePersonality::get_age);
	ClassDB::bind_method(D_METHOD("set_personality_override", "value"), &SocialEnginePersonality::set_personality_override);
	ClassDB::bind_method(D_METHOD("get_personality_override"), &SocialEnginePersonality::get_personality_override);
	ClassDB::bind_method(D_METHOD("set_personality_modifier", "value"), &SocialEnginePersonality::set_personality_modifier);
	ClassDB::bind_method(D_METHOD("get_personality_modifier"), &SocialEnginePersonality::get_personality_modifier);

	//Setup as Properties
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "enthusiasm"), "set_enthusiasm", "get_enthusiasm");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "assertiveness"), "set_assertiveness", "get_assertiveness");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "withdrawal"), "set_withdrawal", "get_withdrawal");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "volatility"), "set_volatility", "get_volatility");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "compassion"), "set_compassion", "get_compassion");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "politeness"), "set_politeness", "get_politeness");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "industriousness"), "set_industriousness", "get_industriousness");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "orderliness"), "set_orderliness", "get_orderliness");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "openness"), "set_openness", "get_openness");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "intellect"), "set_intellect", "get_intellect");
	
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "care_harm"), "set_care_harm", "get_care_harm");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "fairness_cheating"), "set_fairness_cheating", "get_fairness_cheating");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "loyalty_betrayal"), "set_loyalty_betrayal", "get_loyalty_betrayal");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "authority_subversion"), "set_authority_subversion", "get_authority_subversion");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "sanctity_degradation"), "set_sanctity_degradation", "get_sanctity_degradation");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "liberty_oppression"), "set_liberty_oppression", "get_liberty_oppression");
	
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "intelligence"), "set_intelligence", "get_intelligence");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::FLOAT, "maturity"), "set_maturity", "get_maturity");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::INT, "age"), "set_age", "get_age");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::STRING, "personality_override"), "set_personality_override", "get_personality_override");
	ClassDB::add_property("SocialEnginePersonality", PropertyInfo(Variant::STRING, "personality_modifier"), "set_personality_modifier", "get_personality_modifier");
}








