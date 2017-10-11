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

#include <AzCore/Math/Transform.h>
#include <AzCore/Component/EntityBus.h>
#include <AzCore/Component/Component.h>
#include <AzCore/Component/TransformBus.h>
#include <LmbrCentral/Shape/ShapeComponentBus.h>
#include <LmbrCentral/Shape/CompoundShapeComponentBus.h>

namespace LmbrCentral
{
    class CompoundShapeComponent
        : public AZ::Component
        , private ShapeComponentRequestsBus::Handler
        , private ShapeComponentNotificationsBus::MultiHandler
        , private CompoundShapeComponentRequestsBus::Handler
        , public AZ::EntityBus::MultiHandler
    {
    public:

        friend class EditorCompoundShapeComponent;

        AZ_COMPONENT(CompoundShapeComponent, "{C0C817DE-843F-44C8-9FC1-989CDE66B662}");

        CompoundShapeComponent() : 
            m_currentlyActiveChildren(0)
        {}

        //////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;
        //////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////
        // ShapeComponent::Handler implementation
        AZ::Crc32 GetShapeType() override
        {
            return AZ::Crc32("Compound");
        }

        AZ::Aabb GetEncompassingAabb() override;

        bool IsPointInside(const AZ::Vector3& point) override;

        virtual float DistanceSquaredFromPoint(const AZ::Vector3& point) override;
        //////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////
        // CompoundShapeComponentRequestsBus::Handler implementation
        CompoundShapeConfiguration GetCompoundShapeConfiguration() override
        {
            return m_configuration;
        }
        //////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // EntityEvents
        void OnEntityActivated(const AZ::EntityId&) override;
        void OnEntityDeactivated(const AZ::EntityId&) override;
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // ShapeComponentNotificationsBus::MultiHandler
        void OnShapeChanged(ShapeComponentNotifications::ShapeChangeReasons) override;
        ////////////////////////////////////////////////////////////////////////

    protected:

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
        {
            provided.push_back(AZ_CRC("ShapeService", 0xe86aa5fe));
            provided.push_back(AZ_CRC("CompoundShapeService", 0x4f7c640a));
        }

        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
        {
            incompatible.push_back(AZ_CRC("ShapeService", 0xe86aa5fe));
            incompatible.push_back(AZ_CRC("CompoundShapeService", 0x4f7c640a));
        }

        static void Reflect(AZ::ReflectContext* context);

    private:

        //! Stores configuration for this component
        CompoundShapeConfiguration m_configuration;

        //! Number of compound shape children shape entities that are currently active
        int m_currentlyActiveChildren;
    };
} // namespace LmbrCentral
