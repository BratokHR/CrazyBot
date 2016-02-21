#pragma once

#define ET_PLAYER			1
#define EF_CROUCHING		0x00000004
#define EF_PRONE			0x00000008

#define MAX_ENTITIES_IN_SNAPSHOT	256
#define MAX_PLAYERS					64

#define	GENTITYNUM_BITS			10
#define	MAX_GENTITIES			(1<<GENTITYNUM_BITS)
#define	ENTITYNUM_NONE			(MAX_GENTITIES-1)
#define	ENTITYNUM_WORLD			(MAX_GENTITIES-2)
#define	ENTITYNUM_MAX_NORMAL	(MAX_GENTITIES-2)

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

typedef enum {
	qfalse,
	qtrue
}qbool;

typedef enum {
	TEAM_FREE,
	TEAM_AXIS,
	TEAM_ALLIES,
	TEAM_SPECTATOR,
	TEAM_NUM_TEAMS
} team_t;

typedef struct {
	float		fraction;
	vec3_t		endpos;
	int			surfaceFlags;
	qbool		allSolid;
	int			contents;
	short		entityNum;
	short		pad0;
	int			pad1;
} trace_t;

typedef struct {
	qbool		infoValid;
	qbool		unknown;
	int			clientNum;
	char		name[32];
	team_t		team; 
	int			pad[4];
	char		bodymodel[64];
	char		headmodel[64];
	char		helmetmodel[64];

	int			pad1[203];
	int *		pointer;
	int			pad2[11];

	int			movement;

	int			pad3[3];

	qbool		usingMountedWeapon;

	int			pad4;

	int			pose;

	int			pad5[11];

	int *		unknown_ptr;
	int			curWeapon;	

	int			pad6[3];
} clientInfo_t; //size=1208, dw=302

typedef struct
{
    int ServerTime; //0x0000  
    int Buttons; //0x0004  
    char weapon; //0x0008
        char unknown8[3]; //0x0009
    int ViewAngle[3]; //0x000C   
        char unknown24[4]; //0x0018
} userCmd_t;//Size=28
 
typedef struct{
   userCmd_t usercmds[128];  
   int currentCmdNum; 
   userCmd_t *GetUserCmd(int cmdNum)
   {
       int id = cmdNum & 0x7F;
       return &usercmds[id];
   }
} input_t;

typedef struct {
	LPSTR Console;
	LPSTR Normal;
	LPSTR Small;
	LPSTR Big;
	LPSTR ExtraBig;
	LPSTR Bold;
}font_t;

typedef struct {
	LPSTR Cursor;
	LPSTR White;
	LPSTR Black;
	LPSTR GrenadeIcon;
	LPSTR Arrow;
	LPSTR Gradient;
	LPSTR RadarEnemy;
	LPSTR RadarFriend;
}shader_t;

typedef struct {
	int headshot;
	int suicides;
	int death;
	int totalkills;
	int bash;
	int killstreak;
}stats_t;

typedef struct {
	int				x;
	int				y;
	int				width;
	int				height;
	float			fov_x;
	float			fov_y;
	vec3_t			vieworg;
	vec3_t			viewaxis[3];
	int				time;
	int				rdflags;
	BYTE			areamask[8]; //?
} refdef_t; //size=88, dw=22

typedef struct {
	int		trType;
	int		trTime;
	int		trDuration;
	vec3_t	trBase;
	vec3_t	trDelta;
} trajectory_t;

typedef struct {
	int				number;
	int				eType;
	int				eFlags;
	trajectory_t	pos;
	trajectory_t	apos;

	int				pad[8];

	int				otherEntityNum;
	int				otherEntityNum2;

	int				pad4[5];

	int				clientNum;

	int				pad2[2];

	int				solid;
	int				eventParm;

	int				pad5[9];

	int				weapon;
	int				legsAnim;
	int				torsoAnim;

	int				pad3[7];
} entityState_t; //size=240, dw=60

typedef struct {
	entityState_t	currentState;
	entityState_t	nextState;
	qbool			currentValid;
	int				pad[2];
	vec3_t			lerpOrigin;
	vec3_t			lerpAngles;
	int				pad2[8];
} centity_t; //size=548, dw=137

typedef struct {
	int			commandTime;	// cmd->serverTime of last executed command
	int			pm_type;
	int			bobCycle;		// for view bobbing and footstep generation
	int			pm_flags;		// ducked, jump_held, etc
	int			pm_time;
	vec3_t		origin;
	vec3_t		velocity;

	int			padding00[31];

	int			clientNum;

	int			pading01[2422];
} playerState_t; //size=10404, dw=2465

typedef struct {
	int				padding00[12];

	playerState_t	ps;
	int				numEntities;

	int				padding01;

	entityState_t	entities[ MAX_ENTITIES_IN_SNAPSHOT ];
} snapshot_t;

typedef struct {
	int				clientFrame;
	int				clientNum;

	int				padding[7];

	snapshot_t *	snap;
	snapshot_t *	nextSnap;

	int				padding0[38624];

	int				frametime;
	int				time;
	
	int				padding05[4];

	playerState_t	predictedPlayerState;
	
	int				padding5[202];

	//41308
	refdef_t		refdef; //22
	vec3_t			refdefViewAngles;

	int				padding2[3582];
	int				crosshairClientNum;
	int				crosshairClientTime;
	int				padding3[3];
	int				crosshairClientHealth; //?
	int				padding4[173];

	vec3_t			kick_angles;
	int				padding1[205375];

	//int				padding1[209139];
} cg_t; //size=1001888, dw=250472

typedef struct {
	int			vidWidth;
	int			vidHeight;

	int			padding01[125];

	int			voteTime;
} cgs_t; //size=174420, dw=43605
//start=014C3700
//end  =014EE054

typedef struct {
	vec3_t axis[3];
	vec3_t origin;
} orientation_t;

typedef struct {
	centity_t *		cent;
	clientInfo_t *	ci;
	bool			enemy;
	bool			visible;
	bool			alive;
	int				fov_x;
	int				fov_y;
	float			distance;
	float *			color;
	vec3_t			aimangles;
} BotTarger_t;

class crazybot {
public:
	font_t		fonts;
	shader_t	shaders;
	char		path[MAX_PATH];
	HMODULE		hModule;
	stats_t		stats;
	bool		init;

	cg_t *			cg;
	cgs_t *			cgs;
	clientInfo_t *	clientinfo;
	centity_t *		cg_entities;
	input_t *		input;
	userCmd_t		*cmd, *oldcmd, *nextcmd;
	float *			viewangles;
	int *			ping;
	bool *			inGame;
	int *			inMenu;
	bool			InitSettings;

	DWORD			gfx_endframe;
	DWORD			obituary;

	DWORD			trace;
	DWORD			lerptag;
	DWORD			gethandle;
	DWORD			gettagnumber;

	DWORD			MenuOpen;
	DWORD			Attack;
	DWORD			Wallhack;
	DWORD			NoRecoil;
	DWORD			CvarUnlocker1;
	DWORD			CvarUnlocker2;
	DWORD			CvarUnlocker3;
	DWORD			Fov_x;

	xcommand_t		OpenConsole;

	void			InitVersion();
};

typedef void (*xcommand_t)( );

extern crazybot				bot;
extern chook *				Hook;
extern POINT				Cursor;
extern vector<BotTarger_t>	Targets;

extern bool Aimkeypress;
extern bool Shoot;