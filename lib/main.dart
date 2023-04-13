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

import 'package:flutter/material.dart';
import 'package:flutter_tracktion_integration/sine_tone_player.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Tracktion Integration',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Flutter Tracktion Integration'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  late SineTonePlayer sineTonePlayer;
  double frequency = 440;

  _MyHomePageState() {
    sineTonePlayer = SineTonePlayer();
  }

  @override
  void dispose() {
    sineTonePlayer.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text('Frequency: ${frequency.toStringAsFixed(2)} hz'),
            Slider(
              min: 20,
              max: 5000,
              value: frequency,
              onChanged: (value) {
                sineTonePlayer.setFrequency(value);
                setState(() {
                  frequency = value;
                });
              },
            ),
            MaterialButton(
              color: Theme.of(context).primaryColor,
              onPressed: () {
                sineTonePlayer.play();
              },
              child: const Text('Play'),
            ),
            const SizedBox(height: 4),
            MaterialButton(
              color: Theme.of(context).primaryColor,
              onPressed: () {
                sineTonePlayer.stop();
              },
              child: const Text('Stop'),
            ),
          ],
        ),
      ),
    );
  }
}
