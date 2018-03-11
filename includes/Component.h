#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

#include <NDK/Entity.hpp>
#include <NDK/Components.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

class GraphicsComponent;
class NodeComponent;
class CollidableComponent;

namespace NzP
{
	class Component
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(TYPE);
		}

	public:
		Component(std::string type = "Component") { TYPE = std::move(type); }
		virtual ~Component() = default;

		virtual const std::string& Type() const { return TYPE; }
		virtual void UpdateEntity(Ndk::EntityHandle entity) const = 0;
		virtual void Save(Ndk::BaseComponent* comp) = 0;
	protected:
		std::string TYPE;
	};
}
#endif // !COMPONENT_H