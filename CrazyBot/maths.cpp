#include "stdafx.h"

vec3_t vec3_origin = { 0.0f, 0.0f, 0.0f };

int CG_Trace( trace_t *result, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int skipNumber, int mask )
{
	return ( ( int (*)( trace_t *result, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int skipNumber, int mask ) )bot.trace )( result, start, mins, maxs, end, skipNumber, mask );
}

qbool WorldToScreen(vec3_t WorldLocation, vec2_t Screen)
{
	vec3_t	vTransformed;

	float px = tan( DEG2RAD( bot.cg->refdef.fov_x ) * 0.5f );
	float py = tan( DEG2RAD( bot.cg->refdef.fov_y ) * 0.5f );

	VectorSubtract( WorldLocation, bot.cg->refdef.vieworg, vTransformed );
	
	float z = DotProduct( vTransformed, bot.cg->refdef.viewaxis[ 0 ] );
	if( z <= 0.001f )
		return qfalse;

	float xc = bot.cg->refdef.width  * 0.5f;
	float yc = bot.cg->refdef.height * 0.5f;

	Screen[0] = xc - DotProduct( vTransformed, bot.cg->refdef.viewaxis[ 1 ] ) * xc / ( z * px );
	Screen[1] = yc - DotProduct( vTransformed, bot.cg->refdef.viewaxis[ 2 ] ) * yc / ( z * py );

    return qtrue;
}

qbool WorldToScreen3D(centity_t *cent, vec2_t Screen, float height, float angle, float dist)
{
	if (cent->lerpAngles[1] < 0) cent->lerpAngles[1] = (360 + cent->lerpAngles[1]);
	float vAngle = cent->lerpAngles[1] + angle;
	vec3_t vPos;
	vPos[0] = cent->lerpOrigin[0] + (float)(dist * (float)cos(vAngle / 58.0f));
	vPos[1] = cent->lerpOrigin[1] + (float)(dist * (float)sin(vAngle / 58.0f));
	vPos[2] = cent->lerpOrigin[2] + height;

	vec2_t vScreen;
	if (!WorldToScreen(vPos, vScreen)) return qfalse;
	Screen[0] = vScreen[0];
	Screen[1] = vScreen[1];
	return qtrue;
}

void GetAngleToOrigin( vec3_t origin, vec3_t angles )
{
	vec3_t entity;
	VectorSubtract( origin, bot.cg->refdef.vieworg, entity );
	vectoangles( entity, angles );

	if( angles[PITCH] > 180.0f)				angles[PITCH] -= 360.0f;
	else if( angles[PITCH] < -180.0f )		angles[PITCH] += 360.0f;
	if( angles[YAW] > 180.0f )				angles[YAW] -= 360.0f;
	else if( angles[YAW] < -180.0f )		angles[YAW] += 360.0f;
	angles[PITCH]	-= bot.cg->refdefViewAngles[PITCH];
	angles[YAW]		-= bot.cg->refdefViewAngles[YAW];
	if( angles[PITCH] > 180.0f )			angles[PITCH] -= 360.0f;
	else if( angles[PITCH] < -180.0f )		angles[PITCH] += 360.0f;
	if( angles[YAW] > 180.0f )				angles[YAW] -= 360.0f;
	else if( angles[YAW] < -180.0f )		angles[YAW] += 360.0f;
}

void vectoangles( const vec3_t value1, vec3_t angles )
{
	float	forward;
	float	yaw, pitch;
	
	if( value1[1] == 0 && value1[0] == 0 )
	{
		yaw = 0;
		if ( value1[2] > 0 )
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		if ( value1[0] )
			yaw = ( atan2 ( value1[1], value1[0] ) * ( 180.0f / M_PI ) );
		else if ( value1[1] > 0 )
			yaw = 90.0f;
		else
			yaw = 270.0f;

		if ( yaw < 0.0f )
			yaw += 360.0f;

		forward = sqrt ( ( value1[0] * value1[0] ) + ( value1[1] * value1[1] ) );
		pitch = ( atan2( value1[2], forward ) * ( 180.0f / M_PI ) );

		if ( pitch < 0.0f )
			pitch += 360;
	}

	angles[PITCH]	= -pitch;
	angles[YAW]		= yaw;
	angles[ROLL]	= 0;
}

bool CG_SetTagOrigin( centity_t * cent, short tag, orientation_t * orient  )
{
	DWORD R_GetHandle = bot.gethandle;
	DWORD R_LerpTag = bot.lerptag;

	__asm
	{
		mov		ebx, cent
		mov		eax, [ebx+220h]
		mov		ecx, [ebx+0F0h]
		call	dword ptr [R_GetHandle]

		test	eax, eax
		jz		no_tag

		mov		ecx, eax
		movzx	eax, tag
		push	orient
		push	cent
		call	dword ptr [R_LerpTag]
		add		esp, 8

		test	eax, eax
		jz		no_tag

		mov		eax, 1

no_tag:
	}
}

short CG_GetTagNumber( const char * tag_name )
{
	return ( ( short (*)( const char *, int, size_t, int ) )bot.gettagnumber )( tag_name, 1, strlen( tag_name ) + 1, 6 );
}

bool IsVisible( vec3_t point )
{
	trace_t t;

	CG_Trace( &t, bot.cg->refdef.vieworg, vec3_origin, vec3_origin, point, bot.cg->snap->ps.clientNum, MASK_TARGET & ~CONTENTS_BODY );

	return ( t.fraction == 1.0f );
}

float GetDistanceXY( vec3_t A, vec3_t B )
{
	float dx = A[0] - B[0];
	float dy = A[1] - B[1];
	float dz = 0;

	return (float)(sqrt( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) ));
}

float GetDistance( vec3_t A, vec3_t B )
{
	float dx = A[0] - B[0];
	float dy = A[1] - B[1];
	float dz = A[2] - B[2];

	return (float)(sqrt( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) )/48);
}

float distance( vec3_t origin )
{
	vec3_t vector;
	
	VectorSub( origin, bot.cg->refdef.vieworg, vector );
	return ( sqrt( vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2] ) / 48 );
}

centity_t * AimingAtEntity( )
{
	trace_t	t;
	vec3_t	end;

	VectorMA( bot.cg->refdef.vieworg, 131072, bot.cg->refdef.viewaxis[0], end );

	CG_Trace( &t, bot.cg->refdef.vieworg, vec3_origin, vec3_origin, end, bot.cg->snap->ps.clientNum, MASK_TARGET | CONTENTS_BODY );

	if( t.fraction != 1.0f )
	{
		centity_t * cent = &bot.cg_entities[ t.entityNum ];
		
		return cent;
	}

	return NULL;
}

clientInfo_t * AimingAtClient( )
{
	centity_t * cent = AimingAtEntity( );

	if( cent && cent->currentState.eType == ET_PLAYER )
		return &bot.clientinfo[ cent->currentState.clientNum ];
	
	return NULL;
}