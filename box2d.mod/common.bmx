' Copyright (c) 2008 Bruce A Henderson
' 
' Permission is hereby granted, free of charge, to any person obtaining a copy
' of this software and associated documentation files (the "Software"), to deal
' in the Software without restriction, including without limitation the rights
' to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, subject to the following conditions:
' 
' The above copyright notice and this permission notice shall be included in
' all copies or substantial portions of the Software.
' 
' THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
' IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
' FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
' AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
' LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
' OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
' THE SOFTWARE.
' 
SuperStrict

Import "source.bmx"

Extern

	Function bmx_b2aabb_create:Byte Ptr(lowerBound:Byte Ptr, upperBound:Byte Ptr)
	Function bmx_b2aabb_delete(handle:Byte Ptr)
	Function bmx_b2abb_setlowerbound(handle:Byte Ptr, lowerBound:Byte Ptr)
	Function bmx_b2abb_setupperbound(handle:Byte Ptr, upperBound:Byte Ptr)
	Function bmx_b2abb_isvalid(handle:Byte Ptr)

	Function bmx_b2vec2_create:Byte Ptr(x:Float, y:Float)
	Function bmx_b2vec2_delete(handle:Byte Ptr)
	Function bmx_b2vec2_getx:Float(handle:Byte Ptr)
	Function bmx_b2vec2_gety:Float(handle:Byte Ptr)
	Function bmx_b2vec2_add(handle:Byte Ptr, vec:Byte Ptr)
	Function bmx_b2vec2_copy(handle:Byte Ptr, vec:Byte Ptr)
	Function bmx_b2vec2_set(handle:Byte Ptr, x:Float, y:Float)
	Function bmx_b2vec2_subtract:Byte Ptr(handle:Byte Ptr, vec:Byte Ptr)
	Function bmx_b2vec2_length:Float(handle:Byte Ptr)
	Function bmx_b2vec2_multiply(handle:Byte Ptr, value:Float)
	Function bmx_b2vec2_plus:Byte Ptr(handle:Byte Ptr, vec:Byte Ptr)
	Function bmx_b2vec2_normalize:Float(handle:Byte Ptr)
	Function bmx_b2vec2_lengthsquared:Float(handle:Byte Ptr)

	Function bmx_b2world_createbody:Byte Ptr(handle:Byte Ptr, def:Byte Ptr, body:Object)
	'Function bmx_b2world_createdynamicbody:Byte Ptr(handle:Byte Ptr, def:Byte Ptr, body:Object)
	Function bmx_b2world_destroybody(handle:Byte Ptr, body:Byte Ptr)
	Function bmx_b2world_getgroundbody:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2world_setwarmstarting(handle:Byte Ptr, flag:Int)
	Function bmx_b2world_setcontinuousphysics(handle:Byte Ptr, flag:Int)
	Function bmx_b2world_validate(handle:Byte Ptr)
	Function bmx_b2world_setdebugDraw(handle:Byte Ptr, debugDraw:Byte Ptr)
	Function bmx_b2world_createjoint:Byte Ptr(handle:Byte Ptr, def:Byte Ptr)
	Function bmx_b2world_destroyjoint(handle:Byte Ptr, joint:Byte Ptr)
	Function bmx_b2world_getbodylist:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2world_getjointlist:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2world_setfilter(handle:Byte Ptr, filter:Byte Ptr)
	Function bmx_b2world_setcontactlistener(handle:Byte Ptr, listener:Byte Ptr)
	Function bmx_b2world_setboundarylistener(handle:Byte Ptr, listener:Byte Ptr)
	Function bmx_b2world_setgravity(handle:Byte Ptr, gravity:Byte Ptr)
	Function bmx_b2world_getcontactlist:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2world_getproxycount:Int(handle:Byte Ptr)
	Function bmx_b2world_getpaircount:Int(handle:Byte Ptr)
	Function bmx_b2world_getbodycount:Int(handle:Byte Ptr)
	Function bmx_b2world_getjointcount:Int(handle:Byte Ptr)
	Function bmx_b2world_free(handle:Byte Ptr)
	Function bmx_b2world_setdestructionlistener(handle:Byte Ptr, listener:Byte Ptr)
	Function bmx_b2world_refilter(handle:Byte Ptr, shape:Byte Ptr)

	Function bmx_b2bodydef_create:Byte Ptr()
	Function bmx_b2bodydef_delete(handle:Byte Ptr)
	'Function bmx_b2bodydef_settype(handle:Byte Ptr, bodyType:Int)
	Function bmx_b2bodydef_setposition(handle:Byte Ptr, position:Byte Ptr)
	Function bmx_b2bodydef_setpositionxy(handle:Byte Ptr, x:Float, y:Float)
	Function bmx_b2bodydef_setangle(handle:Byte Ptr, angle:Float)
	Function bmx_b2bodydef_setmassdata(handle:Byte Ptr, data:Byte Ptr)
	Function bmx_b2bodydef_issleeping:Int(handle:Byte Ptr)
	Function bmx_b2bodydef_setissleeping(handle:Byte Ptr, sleeping:Int)
	Function bmx_b2bodydef_setfixedrotation(handle:Byte Ptr, fixed:Int)
	Function bmx_b2bodydef_getfixedrotation:Int(handle:Byte Ptr)
	Function bmx_b2bodydef_setisbullet(handle:Byte Ptr, bullet:Int)
	Function bmx_b2bodydef_setlineardamping(handle:Byte Ptr, damping:Float)
	Function bmx_b2bodydef_getlineardamping:Float(handle:Byte Ptr)
	Function bmx_b2bodydef_setangulardamping(handle:Byte Ptr, damping:Float)
	Function bmx_b2bodydef_getangulardamping:Float(handle:Byte Ptr)
	Function bmx_b2bodydef_setallowsleep(handle:Byte Ptr, allow:Int)
	Function bmx_b2bodydef_getallowsleep:Int(handle:Byte Ptr)
	Function bmx_b2bodydef_getposition:Byte Ptr(handle:Byte Ptr)

	Function bmx_b2world_create:Byte Ptr(worldAABB:Byte Ptr, gravity:Byte Ptr, doSleep:Int)
	Function bmx_b2world_dostep(handle:Byte Ptr, timeStep:Float, velocityIterations:Int, positionIterations:Int)

	Function bmx_b2shapedef_setfriction(handle:Byte Ptr, friction:Float)
	Function bmx_b2shapedef_setrestitution(handle:Byte Ptr, restitution:Float)
	Function bmx_b2shapedef_setdensity(handle:Byte Ptr, density:Float)
	Function bmx_b2shapedef_setfilter(handle:Byte Ptr, filter:Byte Ptr)
	Function bmx_b2shapedef_getfilter:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2shapedef_setissensor(handle:Byte Ptr, sensor:Int)
	Function bmx_b2shapedef_issensor:Int(handle:Byte Ptr)

	Function bmx_b2polygondef_create:Byte Ptr()
	Function bmx_b2polygondef_setasbox(handle:Byte Ptr, hx:Float, hy:Float)
	Function bmx_b2polygondef_delete(handle:Byte Ptr)
	Function bmx_b2polygondef_setasorientedbox(handle:Byte Ptr, hx:Float, hy:Float, center:Byte Ptr, angle:Float)

	Function bmx_b2body_createshape:Byte Ptr(handle:Byte Ptr, def:Byte Ptr, shape:Object)
	Function bmx_b2body_destroyshape(handle:Byte Ptr, shape:Byte Ptr)
	Function bmx_b2body_setmassfromshapes(handle:Byte Ptr)
	Function bmx_b2body_getposition:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2body_getangle:Float(handle:Byte Ptr)
	Function bmx_b2body_getmaxbody:Object(handle:Byte Ptr)
	Function bmx_b2body_getnext:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2body_getshapelist:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2body_isstatic:Int(handle:Byte Ptr)
	Function bmx_b2body_isdynamic:Int(handle:Byte Ptr)
	Function bmx_b2body_isfrozen:Int(handle:Byte Ptr)
	Function bmx_b2body_issleeping:Int(handle:Byte Ptr)
	Function bmx_b2body_allowsleeping(handle:Byte Ptr, flag:Int)
	Function bmx_b2body_wakeup(handle:Byte Ptr)
	Function bmx_b2body_puttosleep(handle:Byte Ptr)
	Function bmx_b2body_isbullet:Int(handle:Byte Ptr)
	Function bmx_b2body_setbullet(handle:Byte Ptr, flag:Int)
	Function bmx_b2body_getworldcenter:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2body_getlocalcenter:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2body_setlinearvelocity(handle:Byte Ptr, v:Byte Ptr)
	Function bmx_b2body_getlinearvelocity:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2body_setangularvelocity(handle:Byte Ptr, omega:Float)
	Function bmx_b2body_getangularvelocity:Float(handle:Byte Ptr)
	Function bmx_b2body_applyforce(handle:Byte Ptr, force:Byte Ptr, point:Byte Ptr)
	Function bmx_b2body_applytorque(handle:Byte Ptr, torque:Float)
	Function bmx_b2body_applyimpulse(handle:Byte Ptr, impulse:Byte Ptr, point:Byte Ptr)
	Function bmx_b2body_getmass:Float(handle:Byte Ptr)
	Function bmx_b2body_getinertia:Float(handle:Byte Ptr)
	Function bmx_b2body_getworldpoint:Byte Ptr(handle:Byte Ptr, localPoint:Byte Ptr)
	Function bmx_b2body_getworldvector:Byte Ptr(handle:Byte Ptr, localVector:Byte Ptr)
	Function bmx_b2body_getlocalpoint:Byte Ptr(handle:Byte Ptr, worldPoint:Byte Ptr)
	Function bmx_b2body_getlocalvector:Byte Ptr(handle:Byte Ptr, worldVector:Byte Ptr)
	Function bmx_b2body_getjointlist:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2body_getxform:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2body_setxform:Int(handle:Byte Ptr, position:Byte Ptr, angle:Float)

	Function bmx_b2debugdraw_create:Byte Ptr(handle:Object)
	Function bmx_b2debugdraw_setflags(handle:Byte Ptr, flags:Int)
	Function bmx_b2debugdraw_getflags:Int(handle:Byte Ptr)
	Function bmx_b2debugdraw_appendflags(handle:Byte Ptr, flags:Int)
	Function bmx_b2debugdraw_clearflags(handle:Byte Ptr, flags:Int)

	Function bmx_b2circledef_create:Byte Ptr()
	Function bmx_b2circledef_setradius(handle:Byte Ptr, radius:Float)
	Function bmx_b2circledef_setlocalposition(handle:Byte Ptr, pos:Byte Ptr)
	Function bmx_b2circledef_delete(handle:Byte Ptr)
	Function bmx_b2circledef_getradius:Float(handle:Byte Ptr)
	Function bmx_b2circledef_getlocalposition:Byte Ptr(handle:Byte Ptr)

	Function bmx_b2shape_issensor:Int(handle:Byte Ptr)
	Function bmx_b2shape_getbody:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2shape_getmaxshape:Object(handle:Byte Ptr)
	Function bmx_b2shape_getnext:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2shape_testpoint:Int(handle:Byte Ptr, xf:Byte Ptr, p:Byte Ptr)
	Function bmx_b2shape_getsweepradius:Float(handle:Byte Ptr)
	Function bmx_b2shape_getfriction:Float(handle:Byte Ptr)
	Function bmx_b2shape_getrestitution:Float(handle:Byte Ptr)
	Function bmx_b2shape_computeaabb(handle:Byte Ptr, aabb:Byte Ptr, xf:Byte Ptr)
	Function bmx_b2shape_computesweptaabb(handle:Byte Ptr, aabb:Byte Ptr, xf1:Byte Ptr, xf2:Byte Ptr)
	Function bmx_b2shape_computemass(handle:Byte Ptr, data:Byte Ptr)
	Function bmx_b2shape_getfilterdata:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2shape_setfilterdata(handle:Byte Ptr, data:Byte Ptr)

	Function bmx_b2jointdef_setcollideconnected(handle:Byte Ptr, collideConnected:Int)
	Function bmx_b2jointdef_getcollideconnected:Int(handle:Byte Ptr)
	Function bmx_b2jointdef_setbody1(handle:Byte Ptr, body:Byte Ptr)
	Function bmx_b2jointdef_getbody1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2jointdef_setbody2(handle:Byte Ptr, body:Byte Ptr)
	Function bmx_b2jointdef_getbody2:Byte Ptr(handle:Byte Ptr)

	Function bmx_b2revolutejointdef_create:Byte Ptr()
	Function bmx_b2revolutejointdef_initialize(handle:Byte Ptr, body1:Byte Ptr, body2:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2revolutejointdef_delete(handle:Byte Ptr)
	Function bmx_b2revolutejointdef_islimitenabled:Int(handle:Byte Ptr)
	Function bmx_b2revolutejointdef_enablelimit(handle:Byte Ptr, limit:Int)
	Function bmx_b2revolutejointdef_getlowerangle:Float(handle:Byte Ptr)
	Function bmx_b2revolutejointdef_setlowerangle(handle:Byte Ptr, angle:Float)
	Function bmx_b2revolutejointdef_getupperangle:Float(handle:Byte Ptr)
	Function bmx_b2revolutejointdef_setupperangle(handle:Byte Ptr, angle:Float)
	Function bmx_b2revolutejointdef_ismotorenabled:Int(handle:Byte Ptr)
	Function bmx_b2revolutejointdef_enablemotor(handle:Byte Ptr, value:Int)
	Function bmx_b2revolutejointdef_getmotorspeed:Float(handle:Byte Ptr)
	Function bmx_b2revolutejointdef_setmotorspeed(handle:Byte Ptr, speed:Float)
	Function bmx_b2revolutejointdef_getmaxmotortorque:Float(handle:Byte Ptr)
	Function bmx_b2revolutejointdef_setmaxmotortorque(handle:Byte Ptr, torque:Float)
	Function bmx_b2revolutejointdef_getlocalanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2revolutejointdef_setlocalanchor1(handle:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2revolutejointdef_getlocalanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2revolutejointdef_setlocalanchor2(handle:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2revolutejointdef_getreferenceangle:Float(handle:Byte Ptr)
	Function bmx_b2revolutejointdef_setreferenceangle(handle:Byte Ptr, angle:Float)

	Function bmx_b2joint_getmaxjoint:Object(handle:Byte Ptr)
	Function bmx_b2joint_getbody1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2joint_getbody2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2joint_getnext:Byte Ptr(handle:Byte Ptr)

	Function bmx_b2massdata_new:Byte Ptr()
	Function bmx_b2massdata_delete(handle:Byte Ptr)
	Function bmx_b2massdata_setmass(handle:Byte Ptr, mass:Float)
	Function bmx_b2massdata_setcenter(handle:Byte Ptr, center:Byte Ptr)
	Function bmx_b2massdata_seti(handle:Byte Ptr, i:Float)

	Function bmx_b2jointedge_getother:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2jointedge_getjoint:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2jointedge_getprev:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2jointedge_getnext:Byte Ptr(handle:Byte Ptr)

	Function bmx_b2contactfilter_new:Byte Ptr(handle:Object)
	Function bmx_b2contactfilter_delete(handle:Byte Ptr)

	Function bmx_b2contactlistener_new:Byte Ptr(handle:Object)
	Function bmx_b2contactlistener_delete(handle:Byte Ptr)

	Function bmx_b2boundarylistener_new:Byte Ptr(handle:Object)
	Function bmx_b2boundarylistener_delete(handle:Byte Ptr)

	Function bmx_b2distancejointdef_new:Byte Ptr()
	Function bmx_b2distancejointdef_setlocalanchor1(handle:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2distancejointdef_getlocalanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2distancejointdef_setlocalanchor2(handle:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2distancejointdef_getlocalanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2distancejointdef_setlength(handle:Byte Ptr, length:Float)
	Function bmx_b2distancejointdef_getlength:Float(handle:Byte Ptr)
	Function bmx_b2distancejointdef_delete(handle:Byte Ptr)
	Function bmx_b2distancejointdef_setfrequencyhz(handle:Byte Ptr, freq:Float)
	Function bmx_b2distancejointdef_setdampingratio(handle:Byte Ptr, ratio:Float)
	Function bmx_b2distancejointdef_initialize(handle:Byte Ptr, body1:Byte Ptr, body2:Byte Ptr, anchor1:Byte Ptr, anchor2:Byte Ptr)

	Function bmx_b2prismaticjointdef_create:Byte Ptr()
	Function bmx_b2prismaticjointdef_enablelimit(handle:Byte Ptr, value:Int)
	Function bmx_b2prismaticjointdef_islimitenabled:Int(handle:Byte Ptr)
	Function bmx_b2prismaticjointdef_setlowertranslation(handle:Byte Ptr, translation:Float)
	Function bmx_b2prismaticjointdef_getlowertranslation:Float(handle:Byte Ptr)
	Function bmx_b2prismaticjointdef_setuppertranslation(handle:Byte Ptr, translation:Float)
	Function bmx_b2prismaticjointdef_getuppertranslation:Float(handle:Byte Ptr)
	Function bmx_b2prismaticjointdef_enablemotor(handle:Byte Ptr, value:Int)
	Function bmx_b2prismaticjointdef_ismotorenabled:Int(handle:Byte Ptr)
	Function bmx_b2prismaticjointdef_setmaxmotorforce(handle:Byte Ptr, force:Float)
	Function bmx_b2prismaticjointdef_getmaxmotorforce:Float(handle:Byte Ptr)
	Function bmx_b2prismaticjointdef_setmotorspeed(handle:Byte Ptr, speed:Float)
	Function bmx_b2prismaticjointdef_getmotorspeed:Float(handle:Byte Ptr)
	Function bmx_b2prismaticjointdef_delete(handle:Byte Ptr)
	Function bmx_b2prismaticjointdef_initialize(handle:Byte Ptr, body1:Byte Ptr, body2:Byte Ptr, ..
			anchor:Byte Ptr, axis:Byte Ptr)
	Function bmx_b2prismaticjointdef_setlocalanchor1(handle:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2prismaticjointdef_getlocalanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2prismaticjointdef_setlocalanchor2(handle:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2prismaticjointdef_getlocalanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2prismaticjointdef_setlocalaxis1(handle:Byte Ptr, axis:Byte Ptr)
	Function bmx_b2prismaticjointdef_getlocalaxis1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2prismaticjointdef_setreferenceangle(handle:Byte Ptr, angle:Float)
	Function bmx_b2prismaticjointdef_getreferenceangle:Float(handle:Byte Ptr)

	Function bmx_b2revolutejoint_getlowerlimit:Float(handle:Byte Ptr)
	Function bmx_b2revolutejoint_getupperlimit:Float(handle:Byte Ptr)
	Function bmx_b2revolutejoint_setlimits(handle:Byte Ptr, lowerLimit:Float, upperLimit:Float)
	Function bmx_b2revolutejoint_ismotorenabled:Int(handle:Byte Ptr)
	Function bmx_b2revolutejoint_enablemotor(handle:Byte Ptr, flag:Int)
	Function bmx_b2revolutejoint_setmotorspeed(handle:Byte Ptr, speed:Float)
	Function bmx_b2revolutejoint_getmotorspeed:Float(handle:Byte Ptr)
	Function bmx_b2revolutejoint_setmaxmotortorque(handle:Byte Ptr, torque:Float)
	Function bmx_b2revolutejoint_getmotortorque:Float(handle:Byte Ptr)
	Function bmx_b2revolutejoint_islimitenabled:Int(handle:Byte Ptr)
	Function bmx_b2revolutejoint_enablelimit(handle:Byte Ptr, flag:Int)
	Function bmx_b2revolutejoint_getanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2revolutejoint_getanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2revolutejoint_getreactionforce:Byte Ptr(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2revolutejoint_getreactiontorque:Float(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2revolutejoint_getjointangle:Float(handle:Byte Ptr)
	Function bmx_b2revolutejoint_getjointspeed:Float(handle:Byte Ptr)

	Function bmx_b2prismaticjoint_getjointspeed:Float(handle:Byte Ptr)
	Function bmx_b2prismaticjoint_islimitenabled:Int(handle:Byte Ptr)
	Function bmx_b2prismaticjoint_enablelimit(handle:Byte Ptr, flag:Int)
	Function bmx_b2prismaticjoint_getlowerlimit:Float(handle:Byte Ptr)
	Function bmx_b2prismaticjoint_getupperlimit:Float(handle:Byte Ptr)
	Function bmx_b2prismaticjoint_setlimits(handle:Byte Ptr, lowerLimit:Float, upperLimit:Float)
	Function bmx_b2prismaticjoint_ismotorenabled:Int(handle:Byte Ptr)
	Function bmx_b2prismaticjoint_enablemotor(handle:Byte Ptr, flag:Int)
	Function bmx_b2prismaticjoint_setmotorspeed(handle:Byte Ptr, speed:Float)
	Function bmx_b2prismaticjoint_getmotorspeed:Float(handle:Byte Ptr)
	Function bmx_b2prismaticjoint_setmaxmotorforce(handle:Byte Ptr, force:Float)
	Function bmx_b2prismaticjoint_getmotorforce:Float(handle:Byte Ptr)
	Function bmx_b2prismaticjoint_getanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2prismaticjoint_getanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2prismaticjoint_getreactionforce:Byte Ptr(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2prismaticjoint_getreactiontorque:Float(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2prismaticjoint_getjointtranslation:Float(handle:Byte Ptr)

	Function bmx_b2cross:Byte Ptr(a:Byte Ptr, s:Float)
	Function bmx_b2crossf:Byte Ptr(s:Float, a:Byte Ptr)
	Function bmx_b2mul:Byte Ptr(A:Byte Ptr, v:Byte Ptr)
	Function bmx_b2mult:Byte Ptr(A:Byte Ptr, v:Byte Ptr)
	Function bmx_b2mulf:Byte Ptr(T:Byte Ptr, v:Byte Ptr)
	Function bmx_b2multf:Byte Ptr(T:Byte Ptr, v:Byte Ptr)

	Function bmx_b2xform_create:Byte Ptr()
	Function bmx_b2xform_getposition:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2xform_setposition(handle:Byte Ptr, pos:Byte Ptr)
	Function bmx_b2xform_getr:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2xform_setr(handle:Byte Ptr, r:Byte Ptr)
	Function bmx_b2xform_delete(handle:Byte Ptr)

	Function bmx_b2mat22_setangle(handle:Byte Ptr, angle:Float)

	Function bmx_b2contact_getshape1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contact_getshape2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contact_getnext:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contact_issolid:Int(handle:Byte Ptr)
	Function bmx_b2contact_getmanifoldcount:Int(handle:Byte Ptr)

	Function bmx_b2contactresult_getshape1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contactresult_getshape2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contactresult_getposition:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contactresult_getnormal:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contactresult_getnormalimpulse:Float(handle:Byte Ptr)
	Function bmx_b2contactresult_gettangentimpulse:Float(handle:Byte Ptr)

	Function bmx_b2contactpoint_getshape1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contactpoint_getshape2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contactpoint_getposition:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contactpoint_getvelocity:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contactpoint_getnormal:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2contactpoint_getseparation:Float(handle:Byte Ptr)
	Function bmx_b2contactpoint_getfriction:Float(handle:Byte Ptr)
	Function bmx_b2contactpoint_getrestitution:Float(handle:Byte Ptr)

	Function bmx_b2filterdata_create:Byte Ptr()
	Function bmx_b2filterdata_getcategorybits:Short(handle:Byte Ptr)
	Function bmx_b2filterdata_setcategorybits(handle:Byte Ptr, categoryBits:Short)
	Function bmx_b2filterdata_getmaskbits:Short(handle:Byte Ptr)
	Function bmx_b2filterdata_setmaskbits(handle:Byte Ptr, maskBits:Short)
	Function bmx_b2filterdata_getgroupindex:Short(handle:Byte Ptr)
	Function bmx_b2filterdata_setgroupindex(handle:Byte Ptr, index:Short)
	Function bmx_b2filterdata_delete(handle:Byte Ptr)

	Function bmx_b2gearjointdef_new:Byte Ptr()
	Function bmx_b2gearjointdef_setjoint1(handle:Byte Ptr, joint:Byte Ptr)
	Function bmx_b2gearjointdef_setjoint2(handle:Byte Ptr, joint:Byte Ptr)
	Function bmx_b2gearjointdef_setratio(handle:Byte Ptr, ratio:Float)
	Function bmx_b2gearjointdef_delete(handle:Byte Ptr)

	Function bmx_b2gearjoint_getanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2gearjoint_getanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2gearjoint_getreactionforce:Byte Ptr(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2gearjoint_getreactiontorque:Float(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2gearjoint_getratio:Float(handle:Byte Ptr)

	Function bmx_b2mousejoint_getanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2mousejoint_getanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2mousejoint_getreactionforce:Byte Ptr(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2mousejoint_getreactiontorque:Float(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2mousejoint_settarget(handle:Byte Ptr, target:Byte Ptr)
	Function bmx_b2mousejoint_gettarget:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2mousejoint_getlocalanchor:Byte Ptr(handle:Byte Ptr)

	Function bmx_b2pulleyjoint_getanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2pulleyjoint_getanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2pulleyjoint_getreactionforce:Byte Ptr(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2pulleyjoint_getreactiontorque:Float(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2pulleyjoint_getgroundanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2pulleyjoint_getgroundanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2pulleyjoint_getlength1:Float(handle:Byte Ptr)
	Function bmx_b2pulleyjoint_getlength2:Float(handle:Byte Ptr)
	Function bmx_b2pulleyjoint_getratio:Float(handle:Byte Ptr)

	Function bmx_b2distancejoint_getanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2distancejoint_getanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2distancejoint_getreactionforce:Byte Ptr(handle:Byte Ptr, inv_dt:Float)
	Function bmx_b2distancejoint_getreactiontorque:Float(handle:Byte Ptr, inv_dt:Float)

	Function bmx_b2mousejointdef_new:Byte Ptr()
	Function bmx_b2mousejointdef_settarget(handle:Byte Ptr, target:Byte Ptr)
	Function bmx_b2mousejointdef_gettarget:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2mousejointdef_setmaxforce(handle:Byte Ptr, maxForce:Float)
	Function bmx_b2mousejointdef_getmaxforce:Float(handle:Byte Ptr)
	Function bmx_b2mousejointdef_setfrequencyhz(handle:Byte Ptr, frequency:Float)
	Function bmx_b2mousejointdef_getfrequencyhz:Float(handle:Byte Ptr)
	Function bmx_b2mousejointdef_setdampingration(handle:Byte Ptr, ratio:Float)
	Function bmx_b2mousejointdef_getdampingratio:Float(handle:Byte Ptr)
	Function bmx_b2mousejointdef_delete(handle:Byte Ptr)

	Function bmx_b2pulleyjointdef_create:Byte Ptr()
	Function bmx_b2pulleyjointdef_initialize(handle:Byte Ptr, body1:Byte Ptr, body2:Byte Ptr, groundAnchor1:Byte Ptr, ..
		groundAnchor2:Byte Ptr, anchor1:Byte Ptr, anchor2:Byte Ptr, ratio:Float)
	Function bmx_b2pulleyjointdef_setgroundanchor1(handle:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2pulleyjointdef_getgroundanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2pulleyjointdef_setgroundanchor2(handle:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2pulleyjointdef_getgroundanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2pulleyjointdef_setlocalanchor1(handle:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2pulleyjointdef_getlocalanchor1:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2pulleyjointdef_setlocalanchor2(handle:Byte Ptr, anchor:Byte Ptr)
	Function bmx_b2pulleyjointdef_getlocalanchor2:Byte Ptr(handle:Byte Ptr)
	Function bmx_b2pulleyjointdef_setlength1(handle:Byte Ptr, length:Float)
	Function bmx_b2pulleyjointdef_getlength1:Float(handle:Byte Ptr)
	Function bmx_b2pulleyjointdef_setmaxlength1(handle:Byte Ptr, maxLength:Float)
	Function bmx_b2pulleyjointdef_getmaxlength1:Float(handle:Byte Ptr)
	Function bmx_b2pulleyjointdef_setlength2(handle:Byte Ptr, length:Float)
	Function bmx_b2pulleyjointdef_getlength2:Float(handle:Byte Ptr)
	Function bmx_b2pulleyjointdef_setmaxlength2(handle:Byte Ptr, maxLength:Float)
	Function bmx_b2pulleyjointdef_getmaxlength2:Float(handle:Byte Ptr)
	Function bmx_b2pulleyjointdef_setratio(handle:Byte Ptr, ratio:Float)
	Function bmx_b2pulleyjointdef_getratio:Float(handle:Byte Ptr)
	Function bmx_b2pulleyjointdef_delete(handle:Byte Ptr)

	Function bmx_b2destructionlistener_new:Byte Ptr(handle:Object)
	Function bmx_b2destructionlistener_delete(handle:Byte Ptr)

End Extern

Const e_unknownJoint:Int = 0
Const e_revoluteJoint:Int = 1
Const e_prismaticJoint:Int = 2
Const e_distanceJoint:Int = 3
Const e_pulleyJoint:Int = 4
Const e_mouseJoint:Int = 5
Const e_gearJoint:Int = 6

