#include <JoltPlugin/JoltPluginPCH.h>

#include <Core/WorldSerializer/WorldReader.h>
#include <Core/WorldSerializer/WorldWriter.h>
#include <JoltPlugin/Components/JoltSettingsComponent.h>

// clang-format off
EZ_BEGIN_COMPONENT_TYPE(ezJoltSettingsComponent, 1, ezComponentMode::Static)
{
  EZ_BEGIN_PROPERTIES
  {
    EZ_ACCESSOR_PROPERTY("ObjectGravity", GetObjectGravity, SetObjectGravity)->AddAttributes(new ezDefaultValueAttribute(ezVec3(0, 0, -9.81f))),
    EZ_ACCESSOR_PROPERTY("CharacterGravity", GetCharacterGravity, SetCharacterGravity)->AddAttributes(new ezDefaultValueAttribute(ezVec3(0, 0, -12.0f))),
    EZ_ENUM_ACCESSOR_PROPERTY("SteppingMode", ezJoltSteppingMode, GetSteppingMode, SetSteppingMode),
    EZ_ACCESSOR_PROPERTY("FixedFrameRate", GetFixedFrameRate, SetFixedFrameRate)->AddAttributes(new ezDefaultValueAttribute(60.0f), new ezClampValueAttribute(1.0f, 1000.0f)),
    EZ_ACCESSOR_PROPERTY("MaxSubSteps", GetMaxSubSteps, SetMaxSubSteps)->AddAttributes(new ezDefaultValueAttribute(4), new ezClampValueAttribute(1, 100)),
  }
  EZ_END_PROPERTIES;
  EZ_BEGIN_ATTRIBUTES
  {
    new ezCategoryAttribute("Physics/Jolt/Misc"),
  }
  EZ_END_ATTRIBUTES;
}
EZ_END_DYNAMIC_REFLECTED_TYPE;
// clang-format on

ezJoltSettingsComponent::ezJoltSettingsComponent() = default;
ezJoltSettingsComponent::~ezJoltSettingsComponent() = default;

void ezJoltSettingsComponent::SerializeComponent(ezWorldWriter& stream) const
{
  SUPER::SerializeComponent(stream);
  auto& s = stream.GetStream();

  s << m_Settings.m_vObjectGravity;
  s << m_Settings.m_vCharacterGravity;
  s << m_Settings.m_SteppingMode;
  s << m_Settings.m_fFixedFrameRate;
  s << m_Settings.m_uiMaxSubSteps;
}


void ezJoltSettingsComponent::DeserializeComponent(ezWorldReader& stream)
{
  SUPER::DeserializeComponent(stream);
  const ezUInt32 uiVersion = stream.GetComponentTypeVersion(GetStaticRTTI());

  auto& s = stream.GetStream();

  s >> m_Settings.m_vObjectGravity;
  s >> m_Settings.m_vCharacterGravity;
  s >> m_Settings.m_SteppingMode;
  s >> m_Settings.m_fFixedFrameRate;
  s >> m_Settings.m_uiMaxSubSteps;
}

void ezJoltSettingsComponent::SetObjectGravity(const ezVec3& v)
{
  m_Settings.m_vObjectGravity = v;
  SetModified(EZ_BIT(0));
}

void ezJoltSettingsComponent::SetCharacterGravity(const ezVec3& v)
{
  m_Settings.m_vCharacterGravity = v;
  SetModified(EZ_BIT(1));
}

void ezJoltSettingsComponent::SetSteppingMode(ezJoltSteppingMode::Enum mode)
{
  m_Settings.m_SteppingMode = mode;
  SetModified(EZ_BIT(3));
}

void ezJoltSettingsComponent::SetFixedFrameRate(float fFixedFrameRate)
{
  m_Settings.m_fFixedFrameRate = fFixedFrameRate;
  SetModified(EZ_BIT(4));
}

void ezJoltSettingsComponent::SetMaxSubSteps(ezUInt32 uiMaxSubSteps)
{
  m_Settings.m_uiMaxSubSteps = uiMaxSubSteps;
  SetModified(EZ_BIT(5));
}