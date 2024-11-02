import 'package:flutter/material.dart';
import 'package:flutter_joystick/flutter_joystick.dart';
import 'package:stacked/stacked.dart';
import 'package:zone_based_speed_control/ui/views/home/home_viewmodel.dart';

class HomeView extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return ViewModelBuilder<HomeViewModel>.reactive(
      viewModelBuilder: () => HomeViewModel(),
      builder: (context, model, child) => Scaffold(
        appBar: AppBar(
          title: const Text(
            'Zone Based Speed Control',
          ),
          centerTitle: true,
        ),
        backgroundColor: Colors.black,
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Container(
                padding: EdgeInsets.all(16.0),
                decoration: BoxDecoration(
                  color: Colors.blueAccent,
                  borderRadius: BorderRadius.circular(8.0),
                ),
                child: Text(
                  'Direction: ${model.currentDirection}',
                  style: TextStyle(
                      color: Colors.white,
                      fontSize: 28,
                      fontWeight: FontWeight.bold),
                ),
              ),
              SizedBox(height: 60),
              Joystick(
                mode: JoystickMode.all,
                listener: (details) {
                  if (details.x == 0 && details.y == 0) {
                    model.updateDirection('S');
                  } else if (details.y < -0.5) {
                    model.updateDirection('F');
                  } else if (details.y > 0.5) {
                    model.updateDirection('B');
                  } else if (details.x < -0.5) {
                    model.updateDirection('L');
                  } else if (details.x > 0.5) {
                    model.updateDirection('R');
                  }
                },
              ),
            ],
          ),
        ),
      ),
    );
  }
}
