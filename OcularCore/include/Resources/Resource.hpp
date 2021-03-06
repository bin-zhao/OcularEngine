/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#ifndef __H__OCULAR_RESOURCES_RESOURCE__H__
#define __H__OCULAR_RESOURCES_RESOURCE__H__

#include "ResourceType.hpp"
#include "FileIO/File.hpp"
#include "Utilities/TypeInfo.hpp"

#include <cstdint>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        class ResourceMetadata;

        /**
         * \class Resource
         */
        class Resource 
        {
        public:

            /**
             * \param[in] file The source file for the resource.
             */
            Resource(File const& source);
            Resource();

            virtual ~Resource();

            //----------------------------------------
            // Virtual Methods

            /**
             * Frees all memory used by this Resource.
             */
            virtual void unload();

            /**
             * Forces this Resource to be loaded into memory.
             */
            virtual void forceLoad();

            //----------------------------------------
            // Non-Virtual Methods

            /**
             * \return The source file for the resource.
             */
            File getSourceFile() const;

            /**
             * \param[in] file
             * \note This method should generally not be used unless by internal mechanisms.
             */
            void setSourceFile(File const& file);

            /**
             * \param[in] inMemory
             * \note This method should generally not be used unless by internal mechanisms.
             */
            void setIsInMemory(bool inMemory);

            /**
             * \return TRUE if the Resource is loaded in memory.
             */
            bool isInMemory() const;

            /**
             * Sets the size in bytes that this resource occupies when loaded.
             * \param[in] size
             */
            void setSize(uint64_t size);

            /**
             * \return The size, in bytes, of the Resource
             */
            uint64_t getSize() const;

            /**
             * \return The type of resource.
             */
            ResourceType getResourceType() const;

            /**
             *
             */
            void setName(std::string const& name);

            /**
             *
             */
            std::string const& getName() const;

            /**
             * \return The mapping name used to find the resource. This is typically the relative
             *         local path without the file extension.
             */
            std::string const& getMappingName() const;

            /**
             * \note For internal use only
             */
            void setMappingName(std::string const& name);

            /**
             * \return Optional metadata that was set for this Resource. Returns NULL if no metadata set.
             */
            ResourceMetadata* getMetadata() const;

            /** 
             * Sets the optional metadata for this Resource.
             * 
             * The Resource assumes ownership of the metadata and will delete it either at the end of
             * it's lifetime, or during subsequent calls to this methods.
             *
             * \param[in] metadata
             */
            void setMetadata(ResourceMetadata* metadata);

        protected:

            ResourceType m_Type;
            ResourceMetadata* m_Metadata;

            File m_SourceFile;
            bool m_IsInMemory;

            uint64_t m_SizeInMemory;

            std::string m_Name;
            std::string m_MappingName;

        private:

        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

OCULAR_REGISTER_TYPE_CUSTOM(Ocular::Core::Resource, "Resource");

//------------------------------------------------------------------------------------------

#endif
