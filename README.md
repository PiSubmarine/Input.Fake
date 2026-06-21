# Input.Fake

`PiSubmarine.Input.Fake` implements `Input.Api` with synthetic inputs for local development.

It provides:

- `PiSubmarine::Input::Fake::Manager` to create fake `IAxis` and `IKey` instances
- `PiSubmarine::Input::Fake::Binder` to satisfy axis and key capture requests
- `PiSubmarine::Input::Fake::Serializer` to persist and restore fake bindings

Axis values move continuously using deterministic oscillators, while key states pulse periodically. The module is intended for desktop development and UI work where real device input is not available yet.
