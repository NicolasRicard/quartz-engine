// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#pragma once

#include <quartz/core/Core.hpp>

#include <quartz/core/graphics/API/GraphicsResource.hpp>
#include <quartz/core/graphics/API/ITexture.hpp>

#include <unordered_map>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			using TexCache = std::unordered_map<std::string, int>;

			class QZ_API ITextureArray : public ITextureObject
			{
			public:
				static GraphicsResource<ITextureArray> generateTextureArray();
				virtual ~ITextureArray() = default;

				virtual void setOptions(TextureOptions options) = 0;

				virtual void add(const std::string& path) = 0;

				virtual void reserve(const std::string& path) = 0;
				virtual void resolveReservations() = 0;

				virtual const TexCache& getTextureList() const = 0;
				virtual int getTexLayer(const std::string& path) = 0;

			protected:
				ITextureArray() = default;

				TexCache m_texNames;
				TexCache m_texReservations;

				int m_layerNumber = 0;
			};
		}
	}
}

