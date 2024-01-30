// Code for Gothic II Addon (NotR) engine (G2A)

namespace Gothic_II_Addon
{
    auto Hook_zCVobLightData_Unarchive = Union::CreateHook((void*)0x00609FA0, &zCVobLightData::Hook_Unarchive);
    void zCVobLightData::Hook_Unarchive(zCArchiver& arc)
    {
        (this->*Hook_zCVobLightData_Unarchive)(arc);

        zSTRING arg = arc.ReadString("rangeAniScale");

        if (!arg.IsEmpty())
        {
            rangeAniScaleList.EmptyList();

            zSTRING value;
            int i = 1;

            do {
                value = arg.PickWord(i, zSTRING(" "), zSTRING(" "));
                rangeAniScaleList.Insert(value.ToFloat());

                i++;
            } while (!value.IsEmpty());
        }
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