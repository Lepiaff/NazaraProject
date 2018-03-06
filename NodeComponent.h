#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <NDK\Entity.hpp>
#include <NDK\Components.hpp>

#include "Component.h"

namespace NzP
{
	class NodeComponent : public Component
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Component>(*this);
			ar & BOOST_SERIALIZATION_NVP(POSITION_X);
			ar & BOOST_SERIALIZATION_NVP(POSITION_Y);
			ar & BOOST_SERIALIZATION_NVP(SCALE_X);
			ar & BOOST_SERIALIZATION_NVP(SCALE_Y);
			ar & BOOST_SERIALIZATION_NVP(ROTATION_Z);

		}
	public:
		NodeComponent() : Component("NODE_COMPONENT") { ; }
		~NodeComponent() = default;

		virtual void update() { ; }
		virtual const std::string& Type() const { return TYPE; }
		virtual void UpdateEntity(Ndk::EntityHandle entity) const
		{
			Ndk::NodeComponent& nodeComponent = entity->AddComponent<Ndk::NodeComponent>();
			nodeComponent.Move(POSITION_X, POSITION_Y);
			nodeComponent.Scale(SCALE_X, SCALE_Y, 0);
			nodeComponent.Rotate(Nz::EulerAnglesf(0.f, 0.f, ROTATION_Z));
		}

	protected:
		float POSITION_X;
		float POSITION_Y;
		float SCALE_X;
		float SCALE_Y;
		float ROTATION_Z;
	};
}