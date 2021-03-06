/*
This file is part of Bettergram.

For license and copyright information please follow this link:
https://github.com/bettergram/bettergram/blob/master/LEGAL
*/
#pragma once

namespace Ui {

class SendActionAnimation {
public:
	using Type = SendAction::Type;

	void start(Type type);
	void stop();

	int width() const {
		return _impl ? _impl->width() : 0;
	}
	void paint(Painter &p, style::color color, int x, int y, int outerWidth, crl::time ms) {
		if (_impl) {
			_impl->paint(p, color, x, y, outerWidth, ms);
		}
	}

	explicit operator bool() const {
		return _impl != nullptr;
	}

	class Impl {
	public:
		using Type = SendAction::Type;

		Impl(int period) : _period(period), _started(crl::now()) {
		}

		struct MetaData {
			int index;
			std::unique_ptr<Impl> (*creator)();
		};
		virtual const MetaData *metaData() const = 0;
		bool supports(Type type) const;

		virtual int width() const = 0;
		void paint(
			Painter &p,
			style::color color,
			int x,
			int y,
			int outerWidth,
			crl::time ms);

		virtual ~Impl() = default;

	private:
		virtual void paintFrame(Painter &p, style::color color, int x, int y, int outerWidth, int frameMs) = 0;

		int _period = 1;
		crl::time _started = 0;

	};

	~SendActionAnimation();

private:
	std::unique_ptr<Impl> createByType(Type type);

	std::unique_ptr<Impl> _impl;

};

} // namespace Ui
