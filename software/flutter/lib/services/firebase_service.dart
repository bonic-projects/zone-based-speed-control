import 'package:firebase_database/firebase_database.dart';

class FirebaseService {
  final DatabaseReference _database = FirebaseDatabase.instance.ref();

  Future<void> updateDirection(String dbCode, String direction) async {
    try {
      await _database
          .child('devices/jWJC9zONtgbHXSv1vYDpPRsuBFg1/data/direction')
          .set(direction);
    } catch (error) {
      print('Failed to update direction: $error');
    }
  }
}
