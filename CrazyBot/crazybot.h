#define FILTR_MINCROSS			0
#define FILTR_MINDISTANSE		1
#define FILTR_MAXDISTANSE		2

#define FILTR_AUTOAIM			0
#define FILTR_HUMANAIM			1
#define FILTR_SILENTAIM			2

#define FILTR_BONEHELMET		0
#define FILTR_BONEJAW			1
#define FILTR_BONECHEST			2
#define FILTR_BONEPELVIS		3

#define FILTR_ESPALL			0
#define FILTR_ESPENEMY			1
#define FILTR_ESPFRIENDS		2

#define FILTR_BIG				1
#define FILTR_NORMAL			2
#define FILTR_SMALL				3
#define FILTR_BOLD				4

#define FILTR_CROSSCIRCLE		1
#define FILTR_CROSSSQUARE		2
#define FILTR_CROSSCROSSSMALL	3
#define FILTR_CROSSCROSSBIG		4

void GetBoneOriginID(centity_t *entity, char *bone, vec3_t origin);
void AddTargets();
void ClearTargets();
static bool SortPredicateA( BotTarger_t lhs, BotTarger_t rhs);
static bool SortPredicateB( BotTarger_t lhs, BotTarger_t rhs );
static bool SortPredicateC( BotTarger_t lhs, BotTarger_t rhs );
void SortTargets();
void Cheats();