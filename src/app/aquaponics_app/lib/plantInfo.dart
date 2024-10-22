class Plant {
  final String species;
  final String temperature;
  final String ph;
  final String description;
  final String imageUrl;

  Plant({
    required this.species,
    required this.temperature,
    required this.ph,
    required this.description,
    required this.imageUrl,
  });
}

final List<Plant> plants = [
  Plant(
    species: "Plant 1",
    temperature: "0",
    ph: "0",
    description: "",
    imageUrl: "image",
  ),
];