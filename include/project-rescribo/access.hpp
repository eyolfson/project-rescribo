/*
 * Copyright 2019-2020 Jonathan Eyolfson
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 3 as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROJECT_RESCRIBO_ACCESS_HPP
#define PROJECT_RESCRIBO_ACCESS_HPP

#include <cstdint>

namespace project_rescribo {

class Access {
public:
	enum class Flag : uint16_t {
		Public = 0x0001,
		Private = 0x0002,
		Protected = 0x0004,
		Static = 0x0008,
		Final = 0x0010,
		Synchronized  = 0x0020,
		Super = 0x0020,
		Volatile = 0x0040,
		Bridge = 0x0040,
		Transient = 0x0080,
		Varargs = 0x0080,
		Native = 0x0100,
		Interface = 0x0200,
		Abstract = 0x0400,
		Strict = 0x0800,
		Synthetic = 0x1000,
		Annotation = 0x2000,
		Enum = 0x4000,
		Module = 0x8000
	};
	Access() : flags(0) {}
	explicit Access(uint16_t flags) : flags(flags) {}
	uint32_t get_bytes_size() const {
		return 2;
	}

	uint16_t get_flags() const {
		return flags;
	}

	bool is_public() const {
		return flags & static_cast<uint16_t>(Flag::Public);
	}
	bool is_private() const {
		return flags & static_cast<uint16_t>(Flag::Private);
	}
	bool is_protected() const {
		return flags & static_cast<uint16_t>(Flag::Protected);
	}
	bool is_static() const {
		return flags & static_cast<uint16_t>(Flag::Static);
	}
	bool is_final() const {
		return flags & static_cast<uint16_t>(Flag::Final);
	}
	bool is_synchronized() const {
		return flags & static_cast<uint16_t>(Flag::Synchronized);
	}
	bool is_super() const {
		return flags & static_cast<uint16_t>(Flag::Super);
	}
	bool is_volatile() const {
		return flags & static_cast<uint16_t>(Flag::Volatile);
	}
	bool is_bridge() const {
		return flags & static_cast<uint16_t>(Flag::Bridge);
	}
	bool is_transient() const {
		return flags & static_cast<uint16_t>(Flag::Transient);
	}
	bool is_varargs() const {
		return flags & static_cast<uint16_t>(Flag::Varargs);
	}
	bool is_native() const {
		return flags & static_cast<uint16_t>(Flag::Native);
	}
	bool is_interface() const {
		return flags & static_cast<uint16_t>(Flag::Interface);
	}
	bool is_abstract() const {
		return flags & static_cast<uint16_t>(Flag::Abstract);
	}
	bool is_strict() const {
		return flags & static_cast<uint16_t>(Flag::Strict);
	}
	bool is_synthetic() const {
		return flags & static_cast<uint16_t>(Flag::Synthetic);
	}
	bool is_annotation() const {
		return flags & static_cast<uint16_t>(Flag::Annotation);
	}
	bool is_enum() const {
		return flags & static_cast<uint16_t>(Flag::Enum);
	}
	bool is_module() const {
		return flags & static_cast<uint16_t>(Flag::Module);
	}

	void set_public() {
		flags |= static_cast<uint16_t>(Flag::Public);
	}
	void set_private() {
		flags |= static_cast<uint16_t>(Flag::Private);
	}
	void set_protected() {
		flags |= static_cast<uint16_t>(Flag::Protected);
	}
	void set_static() {
		flags |= static_cast<uint16_t>(Flag::Static);
	}
private:
	uint16_t flags;
};

}

#endif
