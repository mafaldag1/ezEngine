#pragma once

#include <Foundation/Basics.h>
#include <Foundation/Configuration/Singleton.h>
#include <Foundation/Configuration/Startup.h>
#include <Foundation/Serialization/AbstractObjectGraph.h>
#include <Foundation/Strings/String.h>
#include <Foundation/Time/Timestamp.h>

struct ezPhantomRttiManagerEvent;

class ezShaderTypeRegistry
{
  EZ_DECLARE_SINGLETON(ezShaderTypeRegistry);

public:
  ezShaderTypeRegistry();
  ~ezShaderTypeRegistry();

  const ezRTTI* GetShaderType(ezStringView sShaderPath);
  const ezRTTI* GetShaderBaseType() const { return m_pBaseType; }

private:
  EZ_MAKE_SUBSYSTEM_STARTUP_FRIEND(EditorFramework, ShaderTypeRegistry);

  struct ShaderData
  {
    ShaderData()

      = default;

    ezString m_sShaderPath;
    ezString m_sAbsShaderPath;
    ezTimestamp m_fileModifiedTime;
    const ezRTTI* m_pType = nullptr;
  };
  void UpdateShaderType(ShaderData& data);
  void PhantomTypeRegistryEventHandler(const ezPhantomRttiManagerEvent& e);

  ezMap<ezString, ShaderData> m_ShaderTypes;
  const ezRTTI* m_pBaseType;
};
