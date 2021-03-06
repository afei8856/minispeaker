 /*
 * Copyright (C) 2014 Ingenic Semiconductor Co., Ltd.
 *	http://www.ingenic.com
 * Author: cli <chen.li@ingenic.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <sound/soc.h>
#include <sound/jack.h>
#include <linux/gpio.h>

static struct snd_soc_ops mensa_i2s_ops = {

};

#ifndef GPIO_PG
#define GPIO_PG(n)      (5*32 + 23 + n)
#endif

static struct snd_soc_dai_link mensa_dais[] = {
	[0] = {
		.name = "PHOENIX ICDC",
		.stream_name = "PHOENIX ICDC",
		.platform_name = "jz-asoc-aic-dma",
		.cpu_dai_name = "jz-asoc-aic-spdif",
		.codec_dai_name = "spdif dump dai",
		.codec_name = "spdif dump",
		.ops = &mensa_i2s_ops,
	},
	[1] = {
		.name = "PHOENIX PCMBT",
		.stream_name = "PHOENIX PCMBT",
		.platform_name = "jz-asoc-pcm-dma",
		.cpu_dai_name = "jz-asoc-pcm",
		.codec_dai_name = "pcm dump dai",
		.codec_name = "pcm dump",
	},
	[2] = {
		.name = "PHOENIX DMIC",
		.stream_name = "PHOENIX DMIC",
		.platform_name = "jz-asoc-dmic-dma",
		.cpu_dai_name = "jz-asoc-dmic",
		.codec_dai_name = "dmic dump dai",
		.codec_name = "dmic dump",
	},
};

static struct snd_soc_card mensa = {
	.name = "phoenix",
	.owner = THIS_MODULE,
	.dai_link = mensa_dais,
	.num_links = ARRAY_SIZE(mensa_dais),
};

static struct platform_device *mensa_snd_device;

static int mensa_init(void)
{
	/*struct jz_aic_gpio_func *gpio_info;*/
	int ret;
	mensa_snd_device = platform_device_alloc("soc-audio", -1);
	if (!mensa_snd_device)
		return -ENOMEM;

	platform_set_drvdata(mensa_snd_device, &mensa);
	ret = platform_device_add(mensa_snd_device);
	if (ret) {
		platform_device_put(mensa_snd_device);
	}

	dev_info(&mensa_snd_device->dev, "Alsa sound card:phoenix init ok!!!\n");
	return ret;
}

static void mensa_exit(void)
{
	platform_device_unregister(mensa_snd_device);
}

module_init(mensa_init);
module_exit(mensa_exit);

MODULE_AUTHOR("shicheng.cheng<shicheng.cheng@ingenic.com>");
MODULE_DESCRIPTION("ALSA SoC mensa Snd Card");
MODULE_LICENSE("GPL");
