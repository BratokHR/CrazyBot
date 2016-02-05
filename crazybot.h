#pragma once
void GetBoneOriginID(centity_t *entity, char *bone, vec3_t origin);
void AddTargets();
void ClearTargets();
static bool SortPredicateA( BotTarger_t lhs, BotTarger_t rhs);
static bool SortPredicateB( BotTarger_t lhs, BotTarger_t rhs );
static bool SortPredicateC( BotTarger_t lhs, BotTarger_t rhs );
void SortTargets();
void Cheats();

extern vector<BotTarger_t> Targets;
extern bool Aimkeypress;
extern cRadar radar;