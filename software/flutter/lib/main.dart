import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:zone_based_speed_control/app/app.bottomsheets.dart';
import 'package:zone_based_speed_control/app/app.dialogs.dart';
import 'package:zone_based_speed_control/app/app.locator.dart';
import 'package:zone_based_speed_control/app/app.router.dart';
import 'package:stacked_services/stacked_services.dart';
import 'package:zone_based_speed_control/firebase_options.dart';

Future<void> main() async {
  await Firebase.initializeApp(
    options: DefaultFirebaseOptions.currentPlatform,
  );
  WidgetsFlutterBinding.ensureInitialized();
  await setupLocator();
  setupDialogUi();
  setupBottomSheetUi();
  runApp(const MainApp());
}

class MainApp extends StatelessWidget {
  const MainApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      initialRoute: Routes.startupView,
      onGenerateRoute: StackedRouter().onGenerateRoute,
      navigatorKey: StackedService.navigatorKey,
      navigatorObservers: [
        StackedService.routeObserver,
      ],
    );
  }
}
