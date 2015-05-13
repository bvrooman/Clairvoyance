#ifndef CLAIRE_MANAGER_H
#define CLAIRE_MANAGER_H

#include "ClairePrerequisites.h"

#include "ClaireSTLContainers.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template <typename T, typename Key>
	class LifetimePolicyOwning
	{
		CLAIRE_MOVABLE_ONLY(LifetimePolicyOwning)

	public:
		using ValueType = std::unique_ptr < T >;
		using Map = unordered_map<Key, ValueType>;

		using PointerType = T*;

	public:
		LifetimePolicyOwning(void) = default;
		~LifetimePolicyOwning(void) = default;

		PointerType get(const Key& key) const
		{
			auto it = mMap.find(key);
			if (it != mMap.end())
			{
				return it->second.get();
			}
			return nullptr;
		}

		template <typename U, typename ...Args>
		PointerType create(const Key& key, Args&& ...args)
		{
			static_assert(
				std::is_base_of<T, U>::value || std::is_same<T, U>::value,
				"Created type must be or derive from base type."
				);

			PointerType p = get(key);
			if (!p)
			{
				p = create_<U>(std::forward<Args>(args)...);
				attach(
					key,
					ValueType(static_cast<PointerType>(p))
					);
			}
			return p;
		}

		void destroy(const Key& key)
		{
			// RAII destruction
			detach(key);
		}

		void attach(const Key& key, ValueType& ptr)
		{
			mMap.insert(Map::value_type(
				key,
				std::move(ptr)
				));
		}

		ValueType detach(const Key& key)
		{
			auto it = mMap.find(key);
			if (it != mMap.end())
			{
				auto p = std::move(it->second);
				mMap.erase(it);
				return p;
			}
			return nullptr;
		}

	private:
		template<typename U, typename ...Args>
		U* create_(Args&& ...args)
		{
			return new U(std::forward<Args>(args)...);
		}

	private:
		Map mMap;
	};


	template <typename T, typename Key>
	class LifetimePolicyNone
	{
	public:
		using ValueType = T*;
		using Map = unordered_map<Key, ValueType>;

		using PointerType = T*;

	public:
		LifetimePolicyNone(void) = default;
		~LifetimePolicyNone(void) = default;

		PointerType get(const Key& key) const
		{
			auto it = mMap.find(key);
			if (it != mMap.end())
			{
				return it->second;
			}
			return nullptr;
		}

		template <typename U, typename ...Args>
		PointerType create(const Key& key, Args&& ...args)
		{
			static_assert(
				std::is_base_of<T, U>::value || std::is_same<T, U>::value,
				"Created type must be or derive from base type."
				);

			PointerType p = get(key);
			if (!p)
			{
				p = create_<U>(std::forward<Args>(args)...);
				attach(
					key,
					ValueType(static_cast<PointerType>(p))
					);
			}
			return p;
		}

		void destroy(const Key& key)
		{
			ValueType p = detach(key);
			if (p)
			{
				delete p;
			}
		}

		void attach(const Key& key, ValueType& ptr)
		{
			mMap.insert(Map::value_type(
				key,
				ptr
				));
		}

		ValueType detach(const Key& key)
		{
			auto it = mMap.find(key);
			if (it != mMap.end())
			{
				ValueType p = it->second;
				mMap.erase(it);
				return p;
			}
			return nullptr;
		}

	private:
		template<typename U, typename ...Args>
		U* create_(Args&& ...args)
		{
			return new U(std::forward<Args>(args)...);
		}

	private:
		Map mMap;
	};


	template <typename Key, typename LifetimePolicy>
	class ManagerBase CLAIRE_FINAL
	{
	private:
		using ValueType = typename LifetimePolicy::ValueType;
		using PointerType = typename LifetimePolicy::PointerType;

	public:
		ManagerBase(void) = default;
		~ManagerBase(void) = default;

		PointerType get(const Key& key) const
		{
			return mLifetimePolicy.get(key);
		}

		template <typename U, typename ...Args>
		PointerType create(const Key& key, Args&& ...args)
		{
			return mLifetimePolicy.create<U>(key, std::forward<Args>(args)...);
		}

		void destroy(const Key& key)
		{
			mLifetimePolicy.destroy(key);
		}

		void attach(const Key& key, ValueType& ptr)
		{
			mLifetimePolicy.attach(key, ptr);
		}

		void attach(const Key& key, ValueType&& ptr)
		{
			mLifetimePolicy.attach(key, std::move(ptr));
		}

		ValueType detach(const Key& key)
		{
			return mLifetimePolicy.detach(key);
		}

	private:
		LifetimePolicy mLifetimePolicy;
	};

	template <typename T, typename Key> using OwningManager		= ManagerBase < Key, LifetimePolicyOwning<T, Key> >;
	template <typename T, typename Key> using Manager			= ManagerBase < Key, LifetimePolicyNone<T, Key> >;

	CLAIRE_NAMESPACE_END
}

#endif