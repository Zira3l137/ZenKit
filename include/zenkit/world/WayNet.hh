// Copyright © 2021-2024 GothicKit Contributors.
// SPDX-License-Identifier: MIT
#pragma once
#include "zenkit/Library.hh"
#include "zenkit/Object.hh"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace zenkit {
	class ReadArchive;

#ifndef ZK_FUTURE
	/// \brief Represents a single waypoint.
	struct WayPoint {
		std::string name;
		std::int32_t water_depth;
		bool under_water;
		Vec3 position;
		Vec3 direction;
		bool free_point {false};
	};

	/// \brief Represents a connection between two waypoints.
	struct WayEdge {
		/// \brief The index of the first waypoint of the connection.
		std::uint32_t a;

		/// \brief The index of the second waypoint of the connection.
		std::uint32_t b;
	};

	/// \brief Represents a way-net.
	///
	/// Way-nets are used for NPC navigation and path finding.
	class WayNet {
	public:
		/// \brief PParses a way-net from the given reader.
		/// \param in The reader to read from.
		/// \return The way-net parsed.
		ZKINT void load(ReadArchive& in);

	public:
		/// \brief All waypoints of this way-net.
		std::vector<WayPoint> waypoints;

		/// \brief All edges of this way-net.
		std::vector<WayEdge> edges;
	};
#else
	/// \brief Represents a single waypoint.
	struct WayPoint : Object {
		ZK_OBJECT(ObjectType::zCWaypoint);

		std::string name;
		std::int32_t water_depth;
		bool under_water;
		Vec3 position;
		Vec3 direction;
		bool free_point {false};

		ZKINT void load(ReadArchive& r, GameVersion version) override;
		ZKINT void save(WriteArchive& w, GameVersion version) const override;
	};

	/// \brief Represents a way-net.
	///
	/// Way-nets are used for NPC navigation and path finding.
	class WayNet : public Object {
		ZK_OBJECT(ObjectType::zCWayNet);

		ZKINT void load(ReadArchive& r, GameVersion version) override;
		ZKINT void save(WriteArchive& w, GameVersion version) const override;

		/// \brief All waypoints of this way-net.
		std::vector<std::shared_ptr<WayPoint>> points;

		/// \brief All edges of this way-net.
		std::vector<std::pair<std::shared_ptr<WayPoint>, std::shared_ptr<WayPoint>>> edges;
	};
#endif
} // namespace zenkit
