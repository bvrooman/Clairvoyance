#ifndef CLAIRE_RENDER_COMMAND_H
#define CLAIRE_RENDER_COMMAND_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireRenderObjectDescriptor.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	CLAIRE_NAMESPACE_BEGIN(renderCommand)

		struct Draw;

	CLAIRE_NAMESPACE_END


	CLAIRE_NAMESPACE_BEGIN(renderCommandDispatch)

		using ReturnType = void;
		using DataType = const void*;

		using RenderCommandDispatchFunction = ReturnType(*)(DataType);

		ReturnType Draw(DataType data)
		{
			const renderCommand::Draw* data_ = union_cast<const renderCommand::Draw*>(data);
			std::cout << "DRAWING LOL" << "\n";
			// render? derp
		}

	CLAIRE_NAMESPACE_END

	using RenderCommandDispatchFunction = renderCommandDispatch::RenderCommandDispatchFunction;


	CLAIRE_NAMESPACE_BEGIN(renderCommand)

		struct Draw
		{
			static const RenderCommandDispatchFunction DISPATCH_FUNCTION;

			uint32_t indexCount;
			uint32_t startIndex;
			uint32_t vertexCount;

			RenderObjectDescriptor renderObjectDescriptor;
		};
		const RenderCommandDispatchFunction Draw::DISPATCH_FUNCTION = &renderCommandDispatch::Draw;

	CLAIRE_NAMESPACE_END


	CLAIRE_NAMESPACE_BEGIN(renderCommandPacket)

		/*
		Command buckets store command packets.
		Each packet holds the following data:
			
			- void* :							A pointer to the next command packet (if any)
			- RenderCommandDispatchFunction :	A pointer to the function responsible for dispatching
												the call to render system command
			- RenderCommand :					The actual command
			- byte* :							Auxiliary memory needed by the command
		*/

		using RenderCommandPacket = void*;

		static const size_t OFFSET_NEXT_RENDER_COMMAND_PACKET = 0u;
		static const size_t OFFSET_RENDER_COMMAND_DISPATCH_FUNCTION = OFFSET_NEXT_RENDER_COMMAND_PACKET + sizeof(RenderCommandPacket);
		static const size_t OFFSET_RENDER_COMMAND = OFFSET_RENDER_COMMAND_DISPATCH_FUNCTION + sizeof(RenderCommandDispatchFunction);

		template <typename RenderCommand>
		RenderCommandPacket create(size_t auxiliaryMemorySize)
		{
			return ::operator new(getSize<RenderCommand>(auxiliaryMemorySize));
		}

		template <typename RenderCommand>
		size_t getSize(size_t auxiliaryMemorySize)
		{
			return OFFSET_RENDER_COMMAND + sizeof(RenderCommand) + auxiliaryMemorySize;
		}

		RenderCommandPacket* getNextRenderCommandPacket(RenderCommandPacket packet)
		{
			return union_cast<RenderCommandPacket*>(reinterpret_cast<byte*>(packet) + OFFSET_NEXT_RENDER_COMMAND_PACKET);
		}

		template <typename RenderCommand>
		RenderCommandPacket* getNextRenderCommandPacket(RenderCommand* command)
		{
			return union_cast<RenderCommandPacket*>(reinterpret_cast<byte*>(command) - OFFSET_RENDER_COMMAND + OFFSET_NEXT_RENDER_COMMAND_PACKET)
		}

		RenderCommandDispatchFunction* getRenderCommandDispatchFunction(RenderCommandPacket packet)
		{
			return union_cast<RenderCommandDispatchFunction*>(reinterpret_cast<byte*>(packet) + OFFSET_RENDER_COMMAND_DISPATCH_FUNCTION);
		}

		template <typename RenderCommand>
		RenderCommand* getRenderCommand(RenderCommandPacket packet)
		{
			return union_cast<RenderCommand*>(reinterpret_cast<byte*>(packet) + OFFSET_RENDER_COMMAND);
		}

		template <typename RenderCommand>
		byte* getAuxiliaryMemory(RenderCommand* command)
		{
			return reinterpret_cast<byte*>(command) + sizeof(RenderCommand);
		}

		void storeNextRenderCommandPacket(RenderCommandPacket packet, RenderCommandPacket nextPacket)
		{
			*getNextRenderCommandPacket(packet) = nextPacket;
		}

		template <typename RenderCommand>
		void storeNextRenderCommandPacket(RenderCommand* command, RenderCommandPacket nextPacket)
		{
			*getNextRenderCommandPacket<RenderCommand>(command) = nextPacket;
		}

		void storeRenderCommandDispatchFunction(RenderCommandPacket packet, RenderCommandDispatchFunction function)
		{
			*getRenderCommandDispatchFunction(packet) = function;
		}

		const RenderCommandPacket loadNextRenderCommandPacket(const RenderCommandPacket packet)
		{
			return *getNextRenderCommandPacket(packet);
		}

		const RenderCommandDispatchFunction loadRenderCommandDispatchFunction(const RenderCommandPacket packet)
		{
			return *getRenderCommandDispatchFunction(packet);
		}

		renderCommandDispatch::DataType loadRenderCommand(const RenderCommandPacket packet)
		{
			return reinterpret_cast<byte*>(packet) + OFFSET_RENDER_COMMAND;
		}

	CLAIRE_NAMESPACE_END

	using RenderCommandPacket = renderCommandPacket::RenderCommandPacket;


	CLAIRE_NAMESPACE_END
}

#endif