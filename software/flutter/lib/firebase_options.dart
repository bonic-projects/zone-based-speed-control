// File generated by FlutterFire CLI.
// ignore_for_file: type=lint
import 'package:firebase_core/firebase_core.dart' show FirebaseOptions;
import 'package:flutter/foundation.dart'
    show defaultTargetPlatform, kIsWeb, TargetPlatform;

/// Default [FirebaseOptions] for use with your Firebase apps.
///
/// Example:
/// ```dart
/// import 'firebase_options.dart';
/// // ...
/// await Firebase.initializeApp(
///   options: DefaultFirebaseOptions.currentPlatform,
/// );
/// ```
class DefaultFirebaseOptions {
  static FirebaseOptions get currentPlatform {
    if (kIsWeb) {
      return web;
    }
    switch (defaultTargetPlatform) {
      case TargetPlatform.android:
        return android;
      case TargetPlatform.iOS:
        return ios;
      case TargetPlatform.macOS:
        return macos;
      case TargetPlatform.windows:
        return windows;
      case TargetPlatform.linux:
        throw UnsupportedError(
          'DefaultFirebaseOptions have not been configured for linux - '
          'you can reconfigure this by running the FlutterFire CLI again.',
        );
      default:
        throw UnsupportedError(
          'DefaultFirebaseOptions are not supported for this platform.',
        );
    }
  }

  static const FirebaseOptions web = FirebaseOptions(
    apiKey: 'AIzaSyD1GMdG9blf7n4fYN4gRyZcJPWu9FqUWIA',
    appId: '1:19231145090:web:f0a20031fa5f87843fc89b',
    messagingSenderId: '19231145090',
    projectId: 'zone-based-speed-control',
    authDomain: 'zone-based-speed-control.firebaseapp.com',
    databaseURL: 'https://zone-based-speed-control-default-rtdb.firebaseio.com',
    storageBucket: 'zone-based-speed-control.firebasestorage.app',
    measurementId: 'G-ZWEE7KPCSX',
  );

  static const FirebaseOptions android = FirebaseOptions(
    apiKey: 'AIzaSyC4uQFOCeyl83Q-zehh5CNX7nDsH91su_c',
    appId: '1:19231145090:android:92c37f726ee712913fc89b',
    messagingSenderId: '19231145090',
    projectId: 'zone-based-speed-control',
    databaseURL: 'https://zone-based-speed-control-default-rtdb.firebaseio.com',
    storageBucket: 'zone-based-speed-control.firebasestorage.app',
  );

  static const FirebaseOptions ios = FirebaseOptions(
    apiKey: 'AIzaSyBYGsS8M-53nqs75JZ-bQz-9mdt6aL9-0w',
    appId: '1:19231145090:ios:be61ed2ad8921c2e3fc89b',
    messagingSenderId: '19231145090',
    projectId: 'zone-based-speed-control',
    databaseURL: 'https://zone-based-speed-control-default-rtdb.firebaseio.com',
    storageBucket: 'zone-based-speed-control.firebasestorage.app',
    iosBundleId: 'com.example.zoneBasedSpeedControl',
  );

  static const FirebaseOptions macos = FirebaseOptions(
    apiKey: 'AIzaSyBYGsS8M-53nqs75JZ-bQz-9mdt6aL9-0w',
    appId: '1:19231145090:ios:be61ed2ad8921c2e3fc89b',
    messagingSenderId: '19231145090',
    projectId: 'zone-based-speed-control',
    databaseURL: 'https://zone-based-speed-control-default-rtdb.firebaseio.com',
    storageBucket: 'zone-based-speed-control.firebasestorage.app',
    iosBundleId: 'com.example.zoneBasedSpeedControl',
  );

  static const FirebaseOptions windows = FirebaseOptions(
    apiKey: 'AIzaSyD1GMdG9blf7n4fYN4gRyZcJPWu9FqUWIA',
    appId: '1:19231145090:web:7f825464c5c2a5a03fc89b',
    messagingSenderId: '19231145090',
    projectId: 'zone-based-speed-control',
    authDomain: 'zone-based-speed-control.firebaseapp.com',
    databaseURL: 'https://zone-based-speed-control-default-rtdb.firebaseio.com',
    storageBucket: 'zone-based-speed-control.firebasestorage.app',
    measurementId: 'G-Z2R0WHP875',
  );

}