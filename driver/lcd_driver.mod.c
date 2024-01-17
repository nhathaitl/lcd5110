#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0x2c111234, "module_layout" },
	{ 0xbaa7d8e7, "kmalloc_caches" },
	{ 0xf9a482f9, "msleep" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x4cb272b1, "gpio_to_desc" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x28118cb6, "__get_user_1" },
	{ 0xa8a31ea5, "misc_register" },
	{ 0x5f754e5a, "memset" },
	{ 0xc5850110, "printk" },
	{ 0x608ccaab, "gpiod_direction_output_raw" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0x26e04dfd, "kmem_cache_alloc_trace" },
	{ 0xfe990052, "gpio_free" },
	{ 0xf1658bf4, "gpiod_set_raw_value" },
	{ 0xadb0e97b, "misc_deregister" },
};

MODULE_INFO(depends, "");

