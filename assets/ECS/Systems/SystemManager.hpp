#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>
#include <data-types.h>

namespace famm {

	class SystemManager
	{
	private:

	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem() {}

		template<typename T>
		void SetSignature(Signature signature) {}


		void EntityDestroyed(Entity entity) {}

		void EntitySignatureChanged(Entity entity, Signature entitySignature) {}



	};

}
#endif