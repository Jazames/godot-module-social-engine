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
	String get_classification();
	String get_response_type();

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


class SocialEnginePersonality : public RefCounted
{
	GDCLASS(SocialEnginePersonality, RefCounted);
public:
	RID self;

	// Big5Traits Getters and Setters
	void set_enthusiasm(double value);
	double get_enthusiasm() const;
	void set_assertiveness(double value);
	double get_assertiveness() const;
	void set_withdrawal(double value);
	double get_withdrawal() const;
	void set_volatility(double value);
	double get_volatility() const;
	void set_compassion(double value);
	double get_compassion() const;
	void set_politeness(double value);
	double get_politeness() const;
	void set_industriousness(double value);
	double get_industriousness() const;
	void set_orderliness(double value);
	double get_orderliness() const;
	void set_openness(double value);
	double get_openness() const;
	void set_intellect(double value);
	double get_intellect() const;

	// MoralFoundations Getters and Setters
	void set_care_harm(double value);
	double get_care_harm() const;
	void set_fairness_cheating(double value);
	double get_fairness_cheating() const;
	void set_loyalty_betrayal(double value);
	double get_loyalty_betrayal() const;
	void set_authority_subversion(double value);
	double get_authority_subversion() const;
	void set_sanctity_degradation(double value);
	double get_sanctity_degradation() const;
	void set_liberty_oppression(double value);
	double get_liberty_oppression() const;

	// Personality Getters and Setters
	void set_intelligence(double value);
	double get_intelligence() const;
	void set_maturity(double value);
	double get_maturity() const;
	void set_age(int value);
	int get_age() const;
	void set_personality_override(String value);
	String get_personality_override() const;
	void set_personality_modifier(String value);
	String get_personality_modifier() const;

	Personality get_underlying_personality() const;
protected:
	static void _bind_methods();
private:
	Personality personality;
};

class SocialEngineAppearance : public RefCounted
{
	GDCLASS(SocialEngineAppearance, RefCounted);
public:
	RID self;

private:
	Appearance appearance;
};


class NpcProperties : public RefCounted
{
	GDCLASS(NpcProperties, RefCounted);

public:

private:
	Appearance appearance;
	Personality personality;
	Knowledge knowledge;
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
	Ref<SocialEngineResponse> generate_npc_response(String dialog, Ref<SocialEnginePersonality> personality);
	void load_LLMs();
	~SocialEngineServer();

private:
    SocialEngineServer();
};





#endif // WRAPPER_H
