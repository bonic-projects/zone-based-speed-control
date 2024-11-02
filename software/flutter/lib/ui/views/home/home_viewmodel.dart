import 'package:firebase_database/firebase_database.dart';
import 'package:stacked/stacked.dart';

class HomeViewModel extends BaseViewModel {
  final DatabaseReference _database = FirebaseDatabase.instance.ref();
  String currentDirection = 'S';

  void updateDirection(String direction) {
    currentDirection = direction;
    try {
      _database
          .child('devices/jWJC9zONtgbHXSv1vYDpPRsuBFg1/data/direction')
          .set(direction);
    } catch (error) {
      print('Failed to update direction: $error');
    }
    notifyListeners();
  }
}
