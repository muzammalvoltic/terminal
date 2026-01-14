// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "pch.h"
#include "Workspace.h"
#include "JsonUtils.h"
#include "ActionAndArgs.h"
#include "WorkspaceTabItem.g.cpp"
#include "Workspace.g.cpp"

using namespace Microsoft::Terminal::Settings::Model;

static constexpr std::string_view NameKey{ "name" };
static constexpr std::string_view TabLayoutKey{ "tabLayout" };

namespace winrt::Microsoft::Terminal::Settings::Model::implementation
{
    // Method Description:
    // - Create a new instance of this class from a serialized JsonObject.
    // Arguments:
    // - json: an object which should be a serialization of a Workspace object.
    // Return Value:
    // - a new Workspace instance created from the values in `json`
    com_ptr<Workspace> Workspace::FromJson(const Json::Value& json)
    {
        auto result = make_self<Workspace>();

        JsonUtils::GetValueForKey(json, NameKey, result->_Name);
        JsonUtils::GetValueForKey(json, TabLayoutKey, result->_TabLayout);

        return result;
    }

    // Method Description:
    // - Create a new serialized JsonObject from an instance of this class
    // Arguments:
    // - <none>
    // Return Value:
    // - the JsonObject representing this instance
    Json::Value Workspace::ToJson() const
    {
        Json::Value json{ Json::ValueType::objectValue };

        JsonUtils::SetValueForKey(json, NameKey, _Name);
        JsonUtils::SetValueForKey(json, TabLayoutKey, _TabLayout);

        return json;
    }

    Model::Workspace Workspace::Copy() const
    {
        auto workspace{ make_self<Workspace>() };
        workspace->_Name = _Name;
        workspace->_TabLayout = winrt::single_threaded_vector<Model::ActionAndArgs>();
        for (const auto& action : _TabLayout)
        {
            workspace->_TabLayout.Append(action.Copy());
        }
        return *workspace;
    }
}
