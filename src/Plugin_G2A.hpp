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

    auto Hook_zCVobLight_DoAnimation = Union::CreateHook((void*)0x006081C0, &zCVobLight::Hook_DoAnimation);
    void zCVobLight::Hook_DoAnimation()
    {
        if (lightData.rangeAniFPS > 0)
        {
            int numFrames = lightData.rangeAniScaleList.GetNumInList();
            if (numFrames > 0)
            {
                int actFrame = int(floor(lightData.rangeAniActFrame));
                float scale = lightData.rangeAniScaleList[actFrame];

                if (lightData.rangeAniSmooth)
                {
                    float percentage = lightData.rangeAniActFrame - actFrame;

                    int nextFrame = actFrame + 1;
                    if (nextFrame >= numFrames)
                        nextFrame = 0;

                    scale += percentage * (lightData.rangeAniScaleList[nextFrame] - scale);
                }

                SetRange(lightData.rangeBackup * scale, FALSE);
                lightData.rangeAniActFrame += lightData.rangeAniFPS * ztimer->frameTimeFloat;

                if (actFrame >= numFrames)
                    lightData.rangeAniActFrame = 0;
            }
        }

        (this->*Hook_zCVobLight_DoAnimation)();
    }
}