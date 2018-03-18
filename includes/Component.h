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
	class Component //A SUPPRIMER, NON UTILISE POUR LE MOMENT
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			//std::cout << "Serialize/Deserialize Component" << std::endl;
			ar & m_type;
			std::cout << "Component _ m_type : " << m_type << std::endl;
			//std::cout << "FIN Serialize/Deserialize Component " << std::endl;
		}

	public:
		Component(std::string type = "Component") { m_type = std::move(type); }
		virtual ~Component() = default;

		virtual const std::string& Type() const { return m_type; }
		virtual void UpdateNazaraEntity(Ndk::EntityHandle entity) const = 0;
		virtual void Save(Ndk::BaseComponent* comp) = 0;
	protected:
		std::string m_type;
	};
}
#endif // !COMPONENT_H