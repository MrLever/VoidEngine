#pragma once
//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "Configurable.h"
#include "EngineInterface.h"

namespace EngineCore {

	//Forward Class declarations
	class WindowManager;

	class Renderer : public EngineUtils::Configurable{
	public:
		/**
		 * Constructor
		 * @param window The Window the renderer draws to
		 */
		Renderer(
			std::shared_ptr<WindowManager> window,
			EngineInterfacePtr engineInterface,
			const EngineUtils::ResourceHandle& configuration
		);

		/**
		 * Destructor
		 */
		~Renderer();

		/** 
		 * Draws to the sceen
		 */
		void Render();

		/**
		 * Applies Renderer Configuration Settings
		 */
		void Configure() override;

	private:
		/** Interface the Renderer uses to access Engine Utility classes */
		std::shared_ptr<EngineInterface> VoidEngineInterface;

		/** Shared with the Input System, the render can draw to this window. */
		std::shared_ptr<WindowManager> Window;
	};

}