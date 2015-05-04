/*
TEST(AllocationPolicyNewDelete, BCPNone_TPSingle)
{
typedef MemoryBoundsCheckingPolicyNone BCP;
typedef MemoryThreadPolicySingle TP;

MemoryArena<MemoryAllocationPolicyNewDelete, TP, BCP> arena;
testArena(arena);
}

TEST(AllocationPolicyNewDelete, BCPSimple_TPSingle)
{
typedef MemoryBoundsCheckingPolicySimple BCP;
typedef MemoryThreadPolicySingle TP;

MemoryArena<MemoryAllocationPolicyNewDelete, TP, BCP> arena;
testArena(arena);
}

TEST(AllocationPolicyNewDelete, BCPNone_TPMulti)
{
typedef MemoryBoundsCheckingPolicyNone BCP;
typedef MemoryThreadPolicyMulti<Mutex> TP;

MemoryArena<MemoryAllocationPolicyNewDelete, TP, BCP> arena;
testArena(arena);
}

TEST(AllocationPolicyNewDelete, BCPSimple_TPMulti)
{
typedef MemoryBoundsCheckingPolicySimple BCP;
typedef MemoryThreadPolicyMulti<Mutex> TP;

MemoryArena<MemoryAllocationPolicyNewDelete, TP, BCP> arena;
testArena(arena);
}
*/