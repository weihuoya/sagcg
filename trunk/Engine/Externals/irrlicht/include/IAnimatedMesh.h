// Copyright (C) 2002-2011 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_ANIMATED_MESH_H_INCLUDED__
#define __I_ANIMATED_MESH_H_INCLUDED__

#include "aabbox3d.h"
#include "IMesh.h"
#include "IAttributes.h"

namespace irr
{
namespace scene
{
	//! Possible types of (animated) meshes.
	enum E_ANIMATED_MESH_TYPE
	{
		//! Unknown animated mesh type.
		EAMT_UNKNOWN = 0,

		//! Quake 2 MD2 model file
		EAMT_MD2,

		//! Quake 3 MD3 model file
		EAMT_MD3,

		//! Maya .obj static model
		EAMT_OBJ,

		//! Quake 3 .bsp static Map
		EAMT_BSP,

		//! 3D Studio .3ds file
		EAMT_3DS,

		//! My3D Mesh, the file format by Zhuck Dimitry
		EAMT_MY3D,

		//! Pulsar LMTools .lmts file. This Irrlicht loader was written by Jonas Petersen
		EAMT_LMTS,

		//! Cartography Shop .csm file. This loader was created by Saurav Mohapatra.
		EAMT_CSM,

		//! .oct file for Paul Nette's FSRad or from Murphy McCauley's Blender .oct exporter.
		/** The oct file format contains 3D geometry and lightmaps and
		can be loaded directly by Irrlicht */
		EAMT_OCT,

		//! Halflife MDL model file
		EAMT_MDL_HALFLIFE,

		//! generic skinned mesh
		EAMT_SKINNED
	};
	
	//! Animation frame loop types
	enum E_ANIMATION_LOOP_TYPE
	{
		//! Looping.
		/** This is the default animation loop type, it plays from
		the start to the end and repeats forever. */
		EALT_LOOP=0,
		//! Plays the animation once.
		EALT_ONCE,
		//! Play the animation forwards, then backwards and repeat.
		EALT_PINGPONG,
		//! There is no animation
		EALT_NONE
	};

	//! Names of animation loop types.
	const c8* const AnimationLoopTypeNames[] =
	{
		"looping",
		"once",
		"pingpong"
		"none",
		0
	};
	
	//! Interface for an animated mesh.
	/** There are already simple implementations of this interface available so
	you don't have to implement this interface on your own if you need to:
	You might want to use irr::scene::SAnimatedMesh, irr::scene::SMesh,
	irr::scene::SMeshBuffer etc. */
	class IAnimatedMesh : public IMesh
	{
	public:

		//! Gets the frame count of the animated mesh.
		/** \deprecated This method no longer makes sense, animated
		meshes are not guaranteed to use keyframes or evenly spaced frames
		to generate the mesh. Instead, use IAnimatedMesh::getAnimation(0)
		to retrieve an io::IAttributes set describing the first animation.
		This method may be removed by Irrlicht 1.10
		/** \return The amount of frames. If the amount is 1,
		it is a static, non animated mesh. */
		_IRR_DEPRECATED_ virtual u32 getFrameCount() const = 0;

		//! Gets the animation speed of the animated mesh.
		/** \return The number of frames per second to play the
		animation with by default. If the amount is 0,
		it is a static, non animated mesh. */
		virtual f32 getAnimationSpeed() const = 0;

		//! Sets the animation speed of the animated mesh.
		/** \param fps Number of frames per second to play the
		animation with by default. If the amount is 0,
		it is not animated. The actual speed is set in the
		scene node the mesh is instantiated in.*/
		virtual void setAnimationSpeed(f32 fps) =0;

		//! Returns the IMesh interface for a frame.
		/** \deprecated This method has been replaced by the other
		getMesh method. Please use that instead. This method may be
		removed by Irrlicht 1.10
		\param frame: Frame number as zero based index. The maximum
		frame number is getFrameCount() - 1;
		\param detailLevel: Level of detail. 0 is the lowest, 255 the
		highest level of detail. Most meshes will ignore the detail level.
		\param startFrameLoop: Because some animated meshes (.MD2) are
		blended between 2 static frames, and maybe animated in a loop,
		the startFrameLoop and the endFrameLoop have to be defined, to
		prevent the animation to be blended between frames which are
		outside of this loop.
		If startFrameLoop and endFrameLoop are both -1, they are ignored.
		\param endFrameLoop: see startFrameLoop.
		\return Returns the animated mesh based on a detail level. */
		_IRR_DEPRECATED_ virtual IMesh* getMesh(s32 frame, s32 detailLevel=255, s32 startFrameLoop=-1, s32 endFrameLoop=-1) = 0;

		//! Returns the type of the animated mesh.
		/** In most cases it is not neccessary to use this method.
		This is useful for making a safe downcast. For example,
		if getMeshType() returns EAMT_MD2 it's safe to cast the
		IAnimatedMesh to IAnimatedMeshMD2.
		\returns Type of the mesh. */
		virtual E_ANIMATED_MESH_TYPE getMeshType() const
		{
			return EAMT_UNKNOWN;
		}
		
		//! Returns the IMesh interface for a frame.
		/**
		\param timeMs The time in milliseconds since the animation
		started.
		\param animationParameters An attribute set containing animation data.
		See IAnimatedMesh::getAnimationData for more information.
		\param levelOfDetail The detail level of the returned mesh, between
		0.0 (lowest) and 1.0 (highest). Most mesh types ignore the detail
		level. */
		virtual IMesh* getMesh(u32 timeMs, io::IAttributes* animationParameters, u32 levelOfDetail=1.0f) = 0;

		//! Returns the number of animation loops provided by this mesh
		/** Every animated mesh type should at least return 1 here, with
		this first animation being the complete animation range.
		\return The total number of animations provided by this mesh. */
		virtual u32 getAnimationCount() const
		{
			return AnimationData.size();
		}

		//! Finds an animation by name
		/** \param name The name to search for, for example "walk" or "stand"
		\return The animation index if it exists, or -1 if the animation was
		not found. */
		virtual s32 getAnimationIndex(const c8* name) const
		{
			for(u32 i=0; i < AnimationData.size(); ++i)
			{
				if(AnimationData[i]->name == name)
					return (s32)i;
			}
			return -1;
		}

		//! Fills the given attribute set with the animation's parameters
		/** The attributes will be cleared.
		Each mesh type stores its animation data internally in its own format,
		this method allows the user to read these parameters, adjust
		them and then call IAnimatedMesh::getMesh to generate an animation
		frame.
		\param index The animation number to return. If this is out of range
		then the default animation (0) will be returned instead.
		\param attribs The io::IAttributes class to be populated
		with data.
		The attribute keys are dependent on the specific type of animated
		mesh:
		<strong>All formats</strong><br/>
		animationId (int) - The animation number that you passed to this
		method. If this field is set when the attributes are passed to
		IAnimatedMesh::getMesh, all other fields may be ignored. This allows
		complex animation data to be read from the internal cache instead of
		parsing the attributes.	If you change any of the other fields then you
		should remove this attribute.<br/>
		animationName (string) - The name of this animation, provided for
		convenience and serialization purposes.<br/>
		animationLength (float) - The amount of time in milliseconds
		that this animation takes to complete. This is used to decide when the
		animation end callback should fire. Looping animations should not set
		this value.
		loopMode (enum) - The scene::E_ANIMATION_LOOP_TYPE of the animation.<br/>

		<strong>Skinned MD2, MD3 and Half-life</strong><br/>
		framesPerSecond - The speed of this animation in frames per second.<br/>
		startFrame (s32) - The first frame of the animation.<br/>
		endFrame (s32) - The last frame of the animation.<br/>

		<strong>Skinned</strong><br/>
		todo: A lot of skinned mesh settings can be moved here.

		<strong>MD3</strong><br/>
		todo: md3 meshes have a loop

		<strong>Half-life</strong><br/>
		todo: anything specific to HL1 meshes?

		\return Returns true if the animation was found, false if not.
		If no animation was found then the data
		*/
		virtual bool getAnimation(s32 index, io::IAttributes** data) const
		{
			if( (index < 0) || (index >= (s32)AnimationData.size()) )
				return false;
		
			*data = AnimationData[index]->data;
			return true;
		}
		
		virtual bool addNamedAnimationData(const c8* name, io::IAttributes* data)
		{
			struct SAnimationData* sdata = new SAnimationData();
			sdata->name = name;
			sdata->data = data;
			AnimationData.push_back(sdata);
			data->grab();
			return true;
		}
				
		//! Animation keyframe which describes a new scale
		struct SAnimationData
		{
			core::stringc name;
			io::IAttributes* data;
		};

	protected:
		
		//! named animations
		core::array< SAnimationData* > AnimationData;
				
	};

} // end namespace scene
} // end namespace irr

#endif

