namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename SynchronizationPrimitive>
	void MemoryThreadPolicyMulti<SynchronizationPrimitive>::enter(void)
	{
		mPrimitive.lock();
	}

	template<typename SynchronizationPrimitive>
	void MemoryThreadPolicyMulti<SynchronizationPrimitive>::leave(void)
	{
		mPrimitive.unlock();
	}

	CLAIRE_NAMESPACE_END
}