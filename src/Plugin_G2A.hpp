// Code for Gothic II Addon (NotR) engine (G2A)

namespace Gothic_II_Addon
{
    void __fastcall zCVobLightData_Partial_Unarchive(Union::Registers& reg);
    auto Hook_zCVobLightData_Unarchive = Union::CreatePartialHook((void*)0x0060A22B, &zCVobLightData_Partial_Unarchive);
    void __fastcall zCVobLightData_Partial_Unarchive(Union::Registers& reg)
    {
        zCVobLightData* self = (zCVobLightData*)reg.edi;
        zSTRING* arg = (zSTRING*)(reg.esp + 0x7c);

        self->rangeAniScaleList.EmptyList();

        zSTRING value;
        int i = 1;

        do {
            value = arg->PickWord(i, zSTRING(" "), zSTRING(" "));
            self->rangeAniScaleList.Insert(value.ToFloat());

            ++i;
        } while (!value.IsEmpty());

        reg.eip = 0x0060A41E;
    }

    auto Hook_zCVobLight_DoAnimation = Union::CreateHook((void*)0x006081C0, &zCVobLight::Hook_DoAnimation, Union::HookType::Hook_Detours);
    void zCVobLight::Hook_DoAnimation()
    {
        if (lightData.rangeAniFPS > 0)
        {
            int numFrames = lightData.rangeAniScaleList.GetNumInList();
            if (numFrames > 0)
            {
                int activeFrame = int(lightData.rangeAniActFrame);
                float scale = lightData.rangeAniScaleList[activeFrame];

                if (lightData.rangeAniSmooth)
                {
                    float fraction = lightData.rangeAniActFrame - activeFrame;

                    int nextFrame = activeFrame + 1;
                    if (nextFrame >= numFrames)
                        nextFrame = 0;

                    scale += fraction * (lightData.rangeAniScaleList[nextFrame] - scale);
                }

                SetRange(lightData.rangeBackup * scale, FALSE);

                lightData.rangeAniActFrame += lightData.rangeAniFPS * ztimer->frameTimeFloat;
                activeFrame = int(lightData.rangeAniActFrame);

                if (lightData.rangeAniActFrame >= numFrames)
                    lightData.rangeAniActFrame -= numFrames * (activeFrame / numFrames);
            }
        }

        (this->*Hook_zCVobLight_DoAnimation)();
    }
}