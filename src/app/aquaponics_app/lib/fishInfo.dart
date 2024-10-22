class Fish {
  final String species;
  final String temperature;
  final String ph;
  final String description;
  final String imageUrl;

  Fish({
    required this.species,
    required this.temperature,
    required this.ph,
    required this.description,
    required this.imageUrl,
  });
}

final List<Fish> fishes = [
  Fish(
    species: "Fish 1",
    temperature: "0",
    ph: "0",
    description: "",
    imageUrl: "image",
  ),
];