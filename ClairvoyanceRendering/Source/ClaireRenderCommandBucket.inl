namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	template <typename T>
	RenderCommandBucket<T>::RenderCommandBucket(size_t size)
	{
		mKeys = new Key[size];
		mPackets = new RenderCommandPacket[size];
	}

	template <typename T>
	RenderCommandBucket<T>::~RenderCommandBucket(void)
	{

	}


	template <typename T>
	template <typename RenderCommand>
	RenderCommand& RenderCommandBucket<T>::addCommand(Key key, size_t auxiliaryMemorySize)
	{
		RenderCommandPacket packet = renderCommandPacket::create<RenderCommand>(auxiliaryMemorySize);

		{
			const size_t currentIndex = mCurrentIndex++;
			mKeys[currentIndex] = key;
			mPackets[currentIndex] = packet;
		}

		renderCommandPacket::storeNextRenderCommandPacket(packet, nullptr);
		renderCommandPacket::storeRenderCommandDispatchFunction(packet, RenderCommand::DISPATCH_FUNCTION);

		return *renderCommandPacket::getRenderCommand<RenderCommand>(packet);
	}

	template <typename T>
	template <typename RenderCommand>
	RenderCommand& RenderCommandBucket<T>::appendCommand(RenderCommand* command, size_t auxiliaryMemorySize)
	{
		RenderCommandPacket packet = renderCommandPacket::create<RenderCommand>(auxiliaryMemorySize);

		// Append the packet to the given command
		renderCommandPacket::storeNextRenderCommandPacket<RenderCommand>(command, packet);

		renderCommandPacket::storeNextRenderCommandPacket(packet, nullptr);
		renderCommandPacket::storeRenderCommandDispatchFunction(packet, RenderCommand::DISPATCH_FUNCTION);

		return renderCommandPacket::getRenderCommand<RenderCommand>(packet);
	}

	template <typename T>
	void RenderCommandBucket<T>::submit(void)
	{
		for (size_t i = 0; i < mCurrentIndex; i++)
		{
			RenderCommandPacket packet = mPackets[i];

			do
			{
				submitRenderCommandPacket(packet);
				packet = renderCommandPacket::loadNextRenderCommandPacket(packet);
			}
			while (packet != nullptr);
		}
	}

	template <typename T>
	void RenderCommandBucket<T>::submitRenderCommandPacket(const RenderCommandPacket packet)
	{
		const RenderCommandDispatchFunction function = renderCommandPacket::loadRenderCommandDispatchFunction(packet);
		renderCommandDispatch::DataType command = renderCommandPacket::loadRenderCommand(packet);
		function(command);
	}

	CLAIRE_NAMESPACE_END
}