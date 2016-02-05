#include "stdafx.h"

void (*CG_Trace)( trace_t *result, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int skipNumber, int mask ) = (void (*)( trace_t *, const vec3_t , const vec3_t , const vec3_t , const vec3_t , int , int ))0x004D8170;

vec3_t vec3_origin = { 0.0f, 0.0f, 0.0f };

DWORD	GetHandle	 = 0x00433DB0;
DWORD	LerpTag	     = 0x004C6AE0;
DWORD   GetTagNumber = 0x00474560;

int CG_GetHandle( centity_t * cent )
{
	__asm
	{
		push ebx
		push ecx

		mov ebx, cent
		mov eax, [ebx+220h]
		mov ecx, [ebx+0F0h]
		call dword ptr [GetHandle]

		pop ecx
		pop ebx
	}
}
int CG_LerpTag( centity_t * cent, orientation_t * _or, short tag, int handle )
{
	__asm
	{
		push	ecx

		mov		ecx, handle
		movzx	eax, tag
		push	_or
		push	cent
		call	dword ptr [LerpTag]
		add		esp, 8

		pop		ecx
	}
}
bool CG_SetTagOrigin( centity_t * cent, short tag, orientation_t * or  )
{

	int handle = CG_GetHandle( cent );

	if( handle )
	{
		if( CG_LerpTag( cent, or, tag, handle ) )
			return true;
	}

	return false;
}

short CG_GetTagNumber( const char * tag_name )
{
	return ( ( short (*)( const char *, int, size_t, int ) )GetTagNumber )( tag_name, 1, strlen( tag_name ) + 1, 6 );

}

float distance( vec3_t origin )
{
	vec3_t vector;
	
	VectorSub( origin, cg->refdef.vieworg, vector );
	return ( sqrt( vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2] )/48 );
}

float GetDistance( vec3_t A, vec3_t B )
{
	float dx = A[0] - B[0];
	float dy = A[1] - B[1];
	float dz = A[2] - B[2];

	return (float)(sqrt( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) )/48);
}

float Get2dDistance( vec2_t A, vec2_t B )
{
	float dx = A[0] - B[0];
	float dy = A[1] - B[1];

	return (float)sqrt( ( dx * dx ) + ( dy * dy ) );
}

bool IsVisible( vec3_t point )
{
	trace_t t;

	CG_Trace( &t, cg->refdef.vieworg, vec3_origin, vec3_origin, point, cg->snap->ps.clientNum, MASK_TARGET & ~CONTENTS_BODY );

	return ( t.fraction == 1.0f );
}

qbool WorldToScreen(vec3_t WorldLocation, vec2_t Screen)
{
	vec3_t	vTransformed;

	float px = tan( DEG2RAD( cg->refdef.fov_x ) * 0.5f );
	float py = tan( DEG2RAD( cg->refdef.fov_y ) * 0.5f );

	VectorSubtract( WorldLocation, cg->refdef.vieworg, vTransformed );
	
	float z = DotProduct( vTransformed, cg->refdef.viewaxis[ 0 ] );
	if( z <= 0.001f )
		return qfalse;

	float xc = cg->refdef.width  * 0.5f;
	float yc = cg->refdef.height * 0.5f;

	Screen[0] = xc - DotProduct( vTransformed, cg->refdef.viewaxis[ 1 ] ) * xc / ( z * px );
	Screen[1] = yc - DotProduct( vTransformed, cg->refdef.viewaxis[ 2 ] ) * yc / ( z * py );

    return qtrue;
}


qbool WorldToScreen3D(vec2_t Screen, float height, float angle, float dist)
{
	/*if (cp->mouse[1] < 0) cp->mouse[1] = (360 + cp->mouse[1]);
	float vAngle = cp->mouse[1] + angle;
	vec3_t vPos;
	vPos[0] = cp->pos[0] + (float)(dist * (float)cos(vAngle / 58.0f));
	vPos[1] = cp->pos[1] + (float)(dist * (float)sin(vAngle / 58.0f));
	vPos[2] = cp->pos[2] + height;

	vec2_t vScreen;
	if (!WorldToScreen(vPos, vScreen)) return qfalse;
	Screen[0] = vScreen[0];
	Screen[1] = vScreen[1];*/
	return qtrue;
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

void AngleVectors( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up)
{
	float			angle;
	static float	sr, sp, sy, cr, cp, cy;

	angle = angles[YAW] * (M_PI*2 / 360);
	sy = sin(angle);
	cy = cos(angle);

	angle = angles[PITCH] * (M_PI*2 / 360);
	sp = sin(angle);
	cp = cos(angle);

	angle = angles[ROLL] * (M_PI*2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1*sr*sp*cy+-1*cr*-sy);
		right[1] = (-1*sr*sp*sy+-1*cr*cy);
		right[2] = -1*sr*cp;
	}
	if (up)
	{
		up[0] = (cr*sp*cy+-sr*-sy);
		up[1] = (cr*sp*sy+-sr*cy);
		up[2] = cr*cp;
	}
}

void AnglesToAxis( const vec3_t angles, vec3_t axis[3] ) {
	vec3_t	right;

	// angle vectors returns "right" instead of "y axis"
	AngleVectors( angles, axis[0], right, axis[2] );
	VectorSubtract( vec3_origin, right, axis[1] );
}

void GetAngleToOrigin( vec3_t origin, vec3_t angles )
{
	vec3_t entity;
	VectorSubtract( origin, cg->refdef.vieworg, entity );
	vectoangles( entity, angles );

	if( angles[PITCH] > 180.0f)				angles[PITCH] -= 360.0f;
	else if( angles[PITCH] < -180.0f )		angles[PITCH] += 360.0f;
	if( angles[YAW] > 180.0f )				angles[YAW] -= 360.0f;
	else if( angles[YAW] < -180.0f )		angles[YAW] += 360.0f;
	angles[PITCH]	-= cg->refdefViewAngles[PITCH];
	angles[YAW]		-= cg->refdefViewAngles[YAW];
	if( angles[PITCH] > 180.0f )			angles[PITCH] -= 360.0f;
	else if( angles[PITCH] < -180.0f )		angles[PITCH] += 360.0f;
	if( angles[YAW] > 180.0f )				angles[YAW] -= 360.0f;
	else if( angles[YAW] < -180.0f )		angles[YAW] += 360.0f;
}

centity_t * AimingAtEntity( )
{
	trace_t	t;
	vec3_t	end;

	VectorMA( cg->refdef.vieworg, 131072, cg->refdef.viewaxis[0], end );

	CG_Trace( &t, cg->refdef.vieworg, vec3_origin, vec3_origin, end, cg->snap->ps.clientNum, MASK_TARGET | CONTENTS_BODY );

	if( t.fraction != 1.0f )
	{
		centity_t * cent = &cg_entities[ t.entityNum ];

		return cent;
	}

	return NULL;
}

clientInfo_t * AimingAtClient( )
{
	centity_t * cent = AimingAtEntity( );

	if( cent && cent->currentState.eType == ET_PLAYER )
		return &clientinfo[ cent->currentState.clientNum ];

	return NULL;
}