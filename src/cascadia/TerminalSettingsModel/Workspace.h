/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- Workspace.h

Abstract:
- A workspace represents a collection of tabs that can be saved and restored.

Author(s):
- Antigravity - January 2026

--*/
#pragma once

#include "WorkspaceTabItem.g.h"
#include "Workspace.g.h"
#include "JsonUtils.h"
#include "ActionAndArgs.h"

namespace winrt::Microsoft::Terminal::Settings::Model::implementation
{
    struct WorkspaceTabItem : WorkspaceTabItemT<WorkspaceTabItem>
    {
    public:
        WorkspaceTabItem() = default;

        WINRT_PROPERTY(hstring, Name);
        WINRT_PROPERTY(hstring, Commandline);
    };

    struct Workspace : WorkspaceT<Workspace>
    {
    public:
        Workspace() = default;

        static com_ptr<Workspace> FromJson(const Json::Value& json);
        Json::Value ToJson() const;
        Model::Workspace Copy() const;

        WINRT_PROPERTY(hstring, Name);
        WINRT_PROPERTY(winrt::Windows::Foundation::Collections::IVector<Model::ActionAndArgs>, TabLayout, winrt::single_threaded_vector<Model::ActionAndArgs>());
    };
}

namespace Microsoft::Terminal::Settings::Model::JsonUtils
{
    using namespace winrt::Microsoft::Terminal::Settings::Model;

    template<>
    struct ConversionTrait<Workspace>
    {
        Workspace FromJson(const Json::Value& json)
        {
            const auto entry = implementation::Workspace::FromJson(json);
            if (entry == nullptr)
            {
                return nullptr;
            }

            return *entry;
        }

        bool CanConvert(const Json::Value& json) const
        {
            return json.isObject();
        }

        Json::Value ToJson(const Workspace& val)
        {
            return winrt::get_self<implementation::Workspace>(val)->ToJson();
        }

        std::string TypeDescription() const
        {
            return "Workspace";
        }
    };
}

namespace winrt::Microsoft::Terminal::Settings::Model::factory_implementation
{
    BASIC_FACTORY(Workspace);
    BASIC_FACTORY(WorkspaceTabItem);
}
