/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

// include the required headers
#include "EMotionFXConfig.h"
#include "EMotionFXManager.h"
#include "BaseObject.h"

MCORE_FORWARD_DECLARE(AttributeSet);


namespace EMotionFX
{
    /**
     * The material base class.
     * This actually acts directly as generic material type. So it is possible for materials to be created from this base class.
     * Other materials are represented by the StandardMaterial class and the FXMaterial class.
     * Every material also has an attribute set with material information. This can be useful when dealing with custom material types in Max or Maya for example.
     * In that case the attribute set will contain information about your material.
     * EMotion Studio could be used to display the contents of this attribute set, or you can use the AttributeSet::Log() method to see some.
     */
    class EMFX_API Material
        : public BaseObject
    {
        MCORE_MEMORYOBJECTCATEGORY(Material, EMFX_DEFAULT_ALIGNMENT, EMFX_MEMCATEGORY_GEOMETRY_MATERIALS);

    public:
        enum
        {
            TYPE_ID = 0x00000000
        };

        /**
         * The creation method.
         * @param name The material name.
         * @result A pointer to a newly created material object of this class.
         */
        static Material* Create(const char* name);

        /**
         * Get the unique type ID of the material.
         * Every material class will have a unique ID which can be used to identify the material type.
         * @result The unique type ID number.
         */
        virtual uint32 GetType() const                      { return TYPE_ID; }

        /**
         * Get the material class description or class name.
         * @result A pointer to the string containing a description or the class name.
         */
        virtual const char* GetTypeString() const           { return "Material"; }

        /**
         * Clone the material.
         * This returns a duplicated version of this material that is exactly the same.
         * @result A pointer to the new material, which is an exact copy of this material.
         */
        virtual Material* Clone() const;

        /**
         * Get the material name.
         * @result The name of the material.
         */
        const char* GetName() const;

        /**
         * Get the material name in String format.
         * @result The name of the material.
         */
        const MCore::String& GetNameString() const;

        /**
         * Set the material name.
         * @param name The new name of the material.
         */
        void SetName(const char* name);

        /**
         * Get the generic attribute set.
         * @result A pointer to the attribute set.
         */
        MCORE_INLINE MCore::AttributeSet* GetAttributeSet() const       { return mAttributeSet; }

    protected:
        uint32                  mNameID;            /**< The material id representing the name. */
        MCore::AttributeSet*    mAttributeSet;      /**< The attribute set. */

        /**
         * The constructor.
         * @param name The name of the material.
         */
        Material(const char* name);

        /**
         * The destructor.
         */
        virtual ~Material();
    };
} // namespace EMotionFX
