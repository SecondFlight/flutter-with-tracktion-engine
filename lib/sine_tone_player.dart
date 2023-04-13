/*
  Copyright (C) 2023 Joshua Wade

  This file is part of a demo to integrate Flutter with Tracktion
  Engine.

  This demo is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This demo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this demo. If not, see <https://www.gnu.org/licenses/>.
*/

import 'dart:ffi';

typedef CreateSineTonePlayerFunc = Pointer Function();
typedef CreateSineTonePlayerFuncDart = Pointer Function();

typedef DestroySineTonePlayerFunc = Void Function(Pointer);
typedef DestroySineTonePlayerFuncDart = void Function(Pointer);

typedef StartPlayingFunc = Void Function(Pointer);
typedef StartPlayingFuncDart = void Function(Pointer);

typedef StopPlayingFunc = Void Function(Pointer);
typedef StopPlayingFuncDart = void Function(Pointer);

typedef SetFrequencyFunc = Void Function(Pointer, Double);
typedef SetFrequencyFuncDart = void Function(Pointer, double);

class SineTonePlayer {
  late final DynamicLibrary dll;

  late final CreateSineTonePlayerFuncDart _createSineTonePlayerFunc;
  late final DestroySineTonePlayerFuncDart _destroySineTonePlayerFunc;
  late final StartPlayingFuncDart _startPlayingFunc;
  late final StopPlayingFuncDart _stopPlayingFunc;
  late final SetFrequencyFuncDart _setFrequencyFunc;

  late final Pointer _sineTonePlayer;

  SineTonePlayer() {
    // This is a hack. We should probably be modifying the Flutter CMake script
    // to bundle this in the same folder as the executable.
    final sineToneDll = DynamicLibrary.open('./data/flutter_assets/assets/DemoEngine.dll');

    _createSineTonePlayerFunc = sineToneDll.lookupFunction<CreateSineTonePlayerFunc, CreateSineTonePlayerFuncDart>('createSineTonePlayer');
    _destroySineTonePlayerFunc = sineToneDll.lookupFunction<DestroySineTonePlayerFunc, DestroySineTonePlayerFuncDart>('destroySineTonePlayer');
    _startPlayingFunc = sineToneDll.lookupFunction<StartPlayingFunc, StartPlayingFuncDart>('startPlaying');
    _stopPlayingFunc = sineToneDll.lookupFunction<StopPlayingFunc, StopPlayingFuncDart>('stopPlaying');
    _setFrequencyFunc = sineToneDll.lookupFunction<SetFrequencyFunc, SetFrequencyFuncDart>('setFrequency');

    _sineTonePlayer = _createSineTonePlayerFunc();
  }

  void dispose() {
    _destroySineTonePlayerFunc(_sineTonePlayer);
  }

  void play() {
    _startPlayingFunc(_sineTonePlayer);
  }

  void stop() {
    _stopPlayingFunc(_sineTonePlayer);
  }

  void setFrequency(double frequency) {
    _setFrequencyFunc(_sineTonePlayer, frequency);
  }
}
