/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef __MASTERANDCOMMANDER_H__
#define __MASTERANDCOMMANDER_H__


#include "../JuceLibraryCode/JuceHeader.h"
#include "model/Parameter.h"
#include "model/SystemConfig.h"
#include <vector>


// forward declarations
class EditorComponent;
class TabMain;
class TabTimbre;
class TabPresetEditor;
class TabPreferences;
class TabAbout;
class IRPlot;
class FreqPlot;
class SampleData;
class PresetCollection;
class HybridReverb2Processor;

struct MetaUpdater;
struct EnvelopeUpdater;
struct TimbreUpdater;
struct GainDelayUpdater;
struct IRPlotUpdater;

class MasterAndCommander
{
public:
    MasterAndCommander(HybridReverb2Processor *ap, const SystemConfig::Ptr &systemConfig);
    ~MasterAndCommander();

    void loadInitialPreset();

    // common methods
    void onGuiReady(void);
    const String & getUserdir();
    String getDBdir();
    const ParamPreferences & getPreferences();
    const ParamPartitionWisdom & getPartitionWisdom();

    // "Main" tab methods
    void registerTabMain(TabMain *tab);
    void onValueChangedPresetNum(int value, std::vector<String> *errors, bool force = false);
    void onValueChangedGainDelay(ParamGainDelay *param);
    void onValueChangedEnvelope(ParamEnvelope *param);

    // "Timbre" tab methods
    void registerTabTimbre(TabTimbre *tab);
    void onValueChangedTimbre(ParamTimbre *param);

    // "Preset Editor" tab methods
    void registerTabPresetEditor(TabPresetEditor *tab);
    void setPresetDB(const std::vector<ParamPreset> & newPresetDB,
                     bool updateManager = true);
    void savePresetDB(const std::vector<ParamPreset> & newPresetDB);
    void savePresetDBas(const std::vector<ParamPreset> & newPresetDB,
                        const String & presetFile);

    // "Preferences" tab methods
    void onValueChangedPreferences(const ParamPreferences & param);

    // "IRPlot" component methods
    void registerIRPlot(IRPlot *plot);

    // "FreqPlot" component methods
    void registerFreqPlot(FreqPlot *plot);

    //
    void setImpulse(const float *data, int len);

private:
    TabTimbre         *tabTimbre = nullptr;
    IRPlot            *irPlot = nullptr;
    FreqPlot          *freqPlot = nullptr;

    typedef ReferenceCountedObjectPtr<SampleData> SampleDataPtr;
    SampleDataPtr dataOriginal;
    SampleDataPtr dataTimbre;
    SampleDataPtr dataModulation;
    SampleDataPtr dataGainDelay;
    SampleDataPtr dataEnvelope;

    ParamPreset       preset;
    ParamPreferences  paramPreferences;
    SystemConfig::Ptr systemConfig;
    std::unique_ptr<PresetCollection>     presetManager;
    HybridReverb2Processor      *audioPlugin = nullptr;
    String           logMessage;
    bool             changeFilter = true;
    bool             enabledTimbre = false;
    bool             enabledModulation = false;
    bool             enabledGainDelay = true;
    bool             enabledEnvelope = true;
    int              currentPreset = -1;

    std::unique_ptr<float[]> impulse;
    int impulseLen = 0;

    void updateOriginal(void);
    void updateTimbre(void);
    void updateModulation(void);
    void updateGainDelay(void);
    void updateEnvelope(void);
    void updateFinal(void);

    const std::unique_ptr<MetaUpdater> metaUpdater;
    const std::unique_ptr<EnvelopeUpdater> envelopeUpdater;
    const std::unique_ptr<TimbreUpdater> timbreUpdater;
    const std::unique_ptr<GainDelayUpdater> gainDelayUpdater;
    const std::unique_ptr<IRPlotUpdater> irPlotUpdater;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterAndCommander)
};


#endif   // __MASTERANDCOMMANDER_H__
