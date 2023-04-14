#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <tracktion_engine/tracktion_engine.h>

void removeAllClips(tracktion::AudioTrack &track)
{
  auto clips = track.getClips();

  for (int i = clips.size(); --i >= 0;)
    clips.getUnchecked(i)->removeFromParent();
}

tracktion::AudioTrack *getOrInsertAudioTrackAt(tracktion::Edit &edit, int index)
{
  edit.ensureNumberOfAudioTracks(index + 1);
  return tracktion::getAudioTracks(edit)[index];
}

tracktion::WaveAudioClip::Ptr loadAudioFileAsClip(tracktion::Edit &edit, const juce::File &file)
{
  // Find the first track and delete all clips from it
  if (auto track = getOrInsertAudioTrackAt(edit, 0))
  {
    removeAllClips(*track);

    // Add a new clip to this track
    tracktion::AudioFile audioFile(edit.engine, file);

    if (audioFile.isValid())
      if (auto newClip = track->insertWaveClip(file.getFileNameWithoutExtension(), file,
                                               {{{}, tracktion::TimeDuration::fromSeconds(audioFile.getLength())}, {}}, false))
        return newClip;
  }

  return {};
}

tracktion::engine::WaveAudioClip::Ptr loopAroundClip(tracktion::engine::WaveAudioClip& clip)
{
  auto &transport = clip.edit.getTransport();
  transport.setLoopRange(clip.getEditTimeRange());
  transport.looping = true;
  transport.setPosition(
    tracktion::core::TimePosition(
      std::chrono::duration<double, std::milli>(0)
    )
  );
  transport.play(false);

  return clip;
}

class TracktionDemoApplication : public juce::JUCEApplicationBase, private juce::ChangeListener
{
private:
  std::unique_ptr<tracktion::Engine> engine;
  std::unique_ptr<tracktion::Project> project;
  std::unique_ptr<tracktion::Edit> edit;

  void changeListenerCallback(juce::ChangeBroadcaster *source) override
  {
    std::cout << "change detected";
  }

public:
  TracktionDemoApplication()
  {
    engine = std::unique_ptr<tracktion::Engine>(new tracktion::Engine("tracktion-engine-demo"));
    edit = tracktion::createEmptyEdit(*engine.get(), juce::File("./test-edit-file"));

    edit->getTransport().addChangeListener(this);
  }

  const juce::String getApplicationName() override { return "JUCE_APPLICATION_NAME_STRING"; }
  const juce::String getApplicationVersion() override { return "0.0.1"; }

  bool moreThanOneInstanceAllowed() override { return true; }

  void anotherInstanceStarted(const juce::String &commandLineParameters) override {}
  void suspended() override {}
  void resumed() override {}
  void shutdown() override {}

  void systemRequestedQuit() override
  {
    setApplicationReturnValue(0);
    quit();
  }

  void unhandledException(const std::exception *exception, const juce::String &sourceFilename,
                          int lineNumber) override
  {
    // This might not work
  }

  void initialise(const juce::String &commandLineParameters) override
  {
    auto f = juce::File("C:\\Users\\joshwade\\Downloads\\monument 7.flac");
    auto clip = loadAudioFileAsClip(*edit, f);
    loopAroundClip(*clip);

    edit->getTransport().play(false);
  }
};

START_JUCE_APPLICATION(TracktionDemoApplication);
