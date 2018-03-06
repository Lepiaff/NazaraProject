#pragma once

#include <string>

#include <NDK/Entity.hpp>

#include <boost/serialization/access.hpp>

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
		Component() = default;
		Component(std::string type = "") { TYPE = std::move(type); }
		~Component() = default;

		virtual void update() = 0;
		virtual const std::string& GetType() const = 0;
		virtual void UpdateEntity(Ndk::EntityHandle entity) const = 0;
	protected:
		std::string TYPE;
	};
}